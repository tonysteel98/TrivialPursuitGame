#include "pch.h"
#include "GameSetup.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "GameFunctions.h"

#include <numeric>
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

// constructor
GameSetup::GameSetup(const std::string& name, int lives_, int questions_)
    : playerName(name), maxLives(lives_), maxQuestions(questions_),
    lives(lives_), score(0), lastCategory(-1), lastPickedIndex(-1)
{
    questionActive = false;
}


// initialize or reset state (GUI or test chooses file)
void GameSetup::initializeGUI() {
    FileReader reader;
    categoryQuestions.clear();
    categoryAnswers.clear();

    for (const auto& file : categoryFiles) {
        auto qs = reader.readQuestions(file);
        auto as = reader.readAnswers(file);
        size_t n = std::min(qs.size(), as.size());
        qs.resize(n);
        as.resize(n);
        categoryQuestions.push_back(qs);
        categoryAnswers.push_back(as);
    }

    lives = maxLives;
    score = 0;
    currentAnswer.clear();
    lastPickedIndex = -1;
    lastCategory = -1;
}



int GameSetup::rollCategory() {
    // build list of non-empty categories
    std::vector<int> availableCategories;
    for (int c = 0; c < (int)categoryQuestions.size(); ++c) {
        for (auto& q : categoryQuestions[c]) {
            if (!q.empty()) {
                availableCategories.push_back(c);
                break;
            }
        }
    }

    if (availableCategories.empty()) {
        return -1; // game over (all categories exhausted)
    }

    GameFunctions gf;
    int pick = gf.rollDice(1, (int)availableCategories.size());
    return availableCategories[pick - 1]; // return category index (0-based)
}


std::pair<std::string, std::string> GameSetup::pickQuestionFromCategory(int category) {
    if (questionActive) {
        return { "Already have a question!", "" }; // block new roll
    }

    auto& qs = categoryQuestions[category];
    auto& as = categoryAnswers[category];

    std::vector<int> available;
    for (int i = 0; i < (int)qs.size(); ++i) {
        if (!qs[i].empty()) available.push_back(i);
    }

    if (available.empty()) {
        return { "", "" };
    }

    GameFunctions gf;
    int idx = available[gf.rollDice(1, available.size()) - 1];

    lastPickedIndex = idx;
    lastCategory = category;
    currentAnswer = as[idx];
    questionActive = true;

    return { qs[idx], currentAnswer };
}


bool GameSetup::submitAnswerForGUI(const std::string& userInput) {
    if (!questionActive || lastPickedIndex == -1 || lastCategory == -1) {
        return false; // no active question
    }

    lastCorrectAnswer = currentAnswer;

    GameFunctions gf;
    bool correct = gf.checkAnswer(userInput, currentAnswer);
    if (correct) ++score;
    else --lives;

    // remove question permanently
    categoryQuestions[lastCategory][lastPickedIndex].clear();
    categoryAnswers[lastCategory][lastPickedIndex].clear();

    lastPickedIndex = -1;
    lastCategory = -1;
    currentAnswer.clear();
    questionActive = false; // now rolling is allowed again
    return correct;
}


void GameSetup::start(bool interactive) {

    if (!interactive) {
        // non-interactive mode: return immediately (safe for tests)
        return;
    }

    // Optional: you could keep console logic here if you want
    // For now, nothing else (GUI handles gameplay).
}

bool GameSetup::saveHighScore() {
    std::ifstream infile("HighScores.csv");
    std::vector<std::tuple<std::string, int>> scores;

    std::string line;
    bool first = true;

    while (std::getline(infile, line)) {
        if (first) { // skip header
            first = false;
            continue;
        }
        std::stringstream ss(line);
        std::string id, player, scoreStr;
        if (std::getline(ss, id, ',') &&
            std::getline(ss, player, ',') &&
            std::getline(ss, scoreStr, ','))
        {
            scores.push_back({ player, std::stoi(scoreStr) });
        }
    }
    infile.close();

    // check if player exists
    bool found = false;
    for (auto& entry : scores) {
        if (std::get<0>(entry) == playerName) {
            found = true;
            // keep the higher score
            if (score > std::get<1>(entry)) {
                std::get<1>(entry) = score;
            }
            break;
        }
    }
    if (!found) {
        scores.push_back({ playerName, score });
    }

    // rewrite file
    std::ofstream outfile("HighScores.csv", std::ios::trunc);
    outfile << "ID,Player,Score\n";
    int id = 1;
    for (auto& entry : scores) {
        outfile << id++ << "," << std::get<0>(entry) << "," << std::get<1>(entry) << "\n";
    }
    outfile.close();

    return true;
}
