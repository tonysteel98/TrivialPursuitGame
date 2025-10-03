#include "pch.h"
#include "FileWriter.h"
#include "FileReader.h" // Needed for duplicate checking
#include <fstream>
#include <sstream>

// Helper function to parse a string by a delimiter
static std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = s.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

bool FileWriter::addQuestion(const std::string& filename, const std::string& question, const std::string& answer) {
    if (question.empty() || answer.empty()) return false;

    // --- Duplicate Check ---
    auto existingQuestions = FileReader::readQuestions(filename);
    for (const auto& q : existingQuestions) {
        if (q == question) {
            return false; // Question already exists
        }
    }

    std::ifstream infile(filename);
    int lastID = 0;
    if (infile.is_open()) {
        std::string line;
        bool first = true;
        while (std::getline(infile, line)) {
            if (first) { first = false; continue; }
            std::stringstream ss(line);
            std::string id_str;
            if (std::getline(ss, id_str, ',')) {
                try {
                    int currentID = std::stoi(id_str);
                    if (currentID > lastID) {
                        lastID = currentID;
                    }
                }
                catch (...) { /* ignore invalid lines */ }
            }
        }
        infile.close();
    }

    std::ofstream outfile(filename, std::ios::app);
    if (!outfile.is_open()) return false;

    outfile << lastID + 1 << "," << question << "," << answer << "\n";
    return true;
}

bool FileWriter::addMultipleFromStrings(const std::string& filename, const std::string& questionsStr, const std::string& answersStr) {
    std::vector<std::string> questions = split(questionsStr, ";;");
    std::vector<std::string> answers = split(answersStr, ";;");

    if (questions.size() != answers.size() || questions.empty()) {
        return false; // Mismatch in number of questions and answers
    }

    // To make this an "all or nothing" operation, we can check all for duplicates first.
    auto existingQuestions = FileReader::readQuestions(filename);
    for (const auto& newQ : questions) {
        for (const auto& oldQ : existingQuestions) {
            if (newQ == oldQ) return false; // Found a duplicate, so we fail the whole batch
        }
    }

    // If all checks pass, add them
    for (size_t i = 0; i < questions.size(); ++i) {
        // Here we call the internal addQuestion, which will re-check, but that's okay.
        // A more optimized way would be a private addQuestionInternal that skips the check.
        if (!addQuestion(filename, questions[i], answers[i])) {
            // This case is unlikely if the above checks passed, but is good for safety
            return false;
        }
    }

    return true;
}