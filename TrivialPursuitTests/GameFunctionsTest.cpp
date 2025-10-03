#include "pch.h"
#include "GameFunctionsTest.h"

void GameFunctionsTest::Test7_InteractiveDiceRoll() {
    std::cout << "\n--- Test 7: Interactive Dice Roll ---\n";
    GameFunctions gf;
    char key = ' ';
    std::cout << "Press any key to roll a 6-sided die, or 'q' to quit.\n";

    // Clear the input buffer before starting the loop
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    do {
        int roll = gf.rollDice(1, 6);
        std::cout << "You rolled a " << roll << "!\n";
        key = std::cin.get();
        // Consume rest of the line if user enters more than one character
        if (key != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (key != 'q' && key != 'Q');

    std::cout << "--- End of Test ---\n";
}

void GameFunctionsTest::Test8_InteractiveAnswerChecker() {
    std::cout << "\n--- Test 8: Case-Sensitive Answer Checker ---\n";
    GameFunctions gf;
    const std::string realAnswer = "Paris";
    std::string userAnswer;

    std::cout << "The correct answer is 'Paris' (note the capitalization).\n";
    std::cout << "\nEnter your guess: ";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userAnswer);

    if (gf.checkAnswer(userAnswer, realAnswer)) {
        std::cout << "Result: CORRECT! Your input matched exactly.\n";
    }
    else {
        std::cout << "Result: INCORRECT. Your input did not match 'Paris'.\n";
    }
    std::cout << "--- End of Test ---\n";
}
