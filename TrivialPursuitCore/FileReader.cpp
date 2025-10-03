#include "pch.h"
#include "FileReader.h"
#include <fstream>
#include <sstream>

std::vector<std::string> FileReader::readQuestions(const std::string& filename) {
    std::vector<std::string> questions;
    std::ifstream file(filename);
    if (!file.is_open()) return questions;

    std::string line;
    bool first = true;
    while (std::getline(file, line)) {
        if (first) { first = false; continue; } // skip header
        std::stringstream ss(line);
        std::string id, q, a;
        if (std::getline(ss, id, ',') &&
            std::getline(ss, q, ',') &&
            std::getline(ss, a, ',')) {
            questions.push_back(q);
        }
    }
    return questions;
}

std::vector<std::string> FileReader::readAnswers(const std::string& filename) {
    std::vector<std::string> answers;
    std::ifstream file(filename);
    if (!file.is_open()) return answers;

    std::string line;
    bool first = true;
    while (std::getline(file, line)) {
        if (first) { first = false; continue; } // skip header
        std::stringstream ss(line);
        std::string id, q, a;
        if (std::getline(ss, id, ',') &&
            std::getline(ss, q, ',') &&
            std::getline(ss, a, ',')) {
            answers.push_back(a);
        }
    }
    return answers;
}

std::vector<std::pair<std::string, int>> FileReader::readHighScores(const std::string& filename) {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(filename);
    if (!file.is_open()) return scores;

    std::string line;
    bool first = true;
    while (std::getline(file, line)) {
        if (first) { first = false; continue; } // skip header
        std::stringstream ss(line);
        std::string id, player, score;
        if (std::getline(ss, id, ',') &&
            std::getline(ss, player, ',') &&
            std::getline(ss, score, ',')) {
            scores.push_back({ player, std::stoi(score) });
        }
    }
    return scores;
}
