#include "pch.h"
#include "GameFunctions.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

int GameFunctions::rollDice(int min, int max) {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned)time(0));
        seeded = true;
    }
    return min + (rand() % (max - min + 1));
}

bool GameFunctions::checkAnswer(const std::string& userInput, const std::string& realAnswer) {
    return userInput == realAnswer;
}

std::pair<std::string, std::string> GameFunctions::pickQuestionAndAnswer(
    const std::vector<std::string>& questions,
    const std::vector<std::string>& answers,
    int index) {

    if (index < 0 || index >= questions.size()) {
        return { "", "" };
    }
    return { questions[index], answers[index] };
}
