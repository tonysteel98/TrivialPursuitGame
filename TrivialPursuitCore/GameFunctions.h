#pragma once
#include <string>
#include <vector>

class GameFunctions {
public:
    int rollDice(int min, int max);
    bool checkAnswer(const std::string& userInput, const std::string& realAnswer);
    std::pair<std::string, std::string> pickQuestionAndAnswer(
        const std::vector<std::string>& questions,
        const std::vector<std::string>& answers,
        int index);
};
