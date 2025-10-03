#include "pch.h"
#include "GameSetupTest.h"

void GameSetupTest::Test9_MiniGameRound() {
    std::cout << "\n--- Test 9: Mini-Game Round Simulation (using TestData.csv) ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    auto questions = FileReader::readQuestions(testFile);
    auto answers = FileReader::readAnswers(testFile);

    if (questions.empty()) {
        std::cout << "TestData.csv is empty or could not be read. Aborting test.\n";
        return;
    }

    GameFunctions gf;
    // Roll for an index within the bounds of the questions vector
    int index = gf.rollDice(0, static_cast<int>(questions.size()) - 1);

    auto qa_pair = gf.pickQuestionAndAnswer(questions, answers, index);
    std::cout << "A random question was picked...\n";
    std::cout << "Question: " << qa_pair.first << std::endl;

    std::string userAnswer;
    std::cout << "Your Answer: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userAnswer);

    if (gf.checkAnswer(userAnswer, qa_pair.second)) {
        std::cout << "That was CORRECT!\n";
    }
    else {
        std::cout << "That was INCORRECT. The right answer was: " << qa_pair.second << "\n";
    }
    std::cout << "--- End of Test ---\n";
}

void GameSetupTest::Test10_CheckGameOverState() {
    std::cout << "\n--- Test 10: Demonstrate Game Over Logic ---\n";
    // This helper creates the dummy category CSVs needed for GameSetup to initialize properly.
    TestHelpers::resetCategoryFiles();

    // Scenario 1: Player runs out of lives.
    std::cout << "Scenario 1: Player runs out of lives.\n";
    GameSetup game1("PlayerOne", 1, 5); // 1 life, 5 points to win
    game1.initializeGUI(); // Loads data from the dummy category files.
    std::cout << "Initial State -> Lives: " << game1.getLives() << ", Score: " << game1.getScore() << ", Game Over: " << (game1.isGameOver() ? "Yes" : "No") << "\n";

    // To test submitting an answer, we must first have an active question.
    int category1 = game1.rollCategory();
    game1.pickQuestionFromCategory(category1);

    // Now, we submit a wrong answer. The internal state is active, so this will work.
    game1.submitAnswerForGUI("a deliberately wrong answer");
    std::cout << "After 1 wrong answer -> Lives: " << game1.getLives() << ", Score: " << game1.getScore() << ", Game Over: " << (game1.isGameOver() ? "Yes" : "No") << "\n";

    std::cout << "\n----------------------------------------\n";

    // Scenario 2: Player reaches the score goal.
    std::cout << "\nScenario 2: Player reaches the score goal.\n";
    GameSetup game2("PlayerTwo", 3, 2); // 3 lives, 2 points to win
    game2.initializeGUI();
    std::cout << "Initial State -> Lives: " << game2.getLives() << ", Score: " << game2.getScore() << ", Game Over: " << (game2.isGameOver() ? "Yes" : "No") << "\n";

    // Simulate two CORRECT answers. We must pick a question and use its actual answer.
    // First correct answer:
    int category2_a = game2.rollCategory();
    auto qa_pair_a = game2.pickQuestionFromCategory(category2_a);
    game2.submitAnswerForGUI(qa_pair_a.second); // Submit the real answer

    // Second correct answer:
    int category2_b = game2.rollCategory();
    auto qa_pair_b = game2.pickQuestionFromCategory(category2_b);
    game2.submitAnswerForGUI(qa_pair_b.second); // Submit the real answer

    std::cout << "After 2 correct answers -> Lives: " << game2.getLives() << ", Score: " << game2.getScore() << ", Game Over: " << (game2.isGameOver() ? "Yes" : "No") << "\n";

    std::cout << "--- End of Test ---\n";
}

