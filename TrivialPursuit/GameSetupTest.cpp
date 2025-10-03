#include "pch.h"
#include "GameSetupTest.h"

// This setup is more complex because GameSetup reads multiple files.
// We will create dummy files just for this test.
void GameSetupTest::setupCategoryFiles() {
    // We only need one file for this test to work.
    std::ofstream outfile("geography.csv", std::ios::trunc);
    outfile << "ID,Question,Answer\n";
    outfile << "1,TestGeoQ1,TestGeoA1\n";
    outfile << "2,TestGeoQ2,TestGeoA2\n";
    outfile.close();

    // Create empty files for the others so the test doesn't fail to find them.
    const std::vector<std::string> otherFiles = { "history.csv", "science.csv", "sports.csv", "movie.csv", "custom.csv" };
    for (const auto& file : otherFiles) {
        std::ofstream emptyFile(file, std::ios::trunc);
        emptyFile << "ID,Question,Answer\n";
        emptyFile.close();
    }
}


void GameSetupTest::TestInitializationAndState() {
    std::cout << "  Running TestInitializationAndState..." << std::endl;
    setupCategoryFiles();

    GameSetup game("Tester", 5, 10);
    game.initializeGUI();

    assert(game.getPlayerName() == "Tester");
    assert(game.getLives() == 5);
    assert(game.getScore() == 0);
    assert(game.getMaxQuestions() == 10);
    assert(game.isGameOver() == false);

    std::cout << "    ...PASSED" << std::endl;
}

void GameSetupTest::TestGameplayLoopStateChanges() {
    std::cout << "  Running TestGameplayLoopStateChanges..." << std::endl;
    setupCategoryFiles();

    GameSetup game("Tester", 3, 10);
    game.initializeGUI();

    // --- Round 1: Correct Answer ---
    int category = game.rollCategory();
    // In our test setup, only category 0 (geography.csv) has questions
    assert(category == 0);

    auto qa_pair = game.pickQuestionFromCategory(category);
    std::string question = qa_pair.first;
    std::string answer = qa_pair.second;

    assert(question.empty() == false);

    bool correct = game.submitAnswerForGUI(answer); // Submit the correct answer
    assert(correct == true);
    assert(game.getScore() == 1);
    assert(game.getLives() == 3);

    // --- Round 2: Incorrect Answer ---
    category = game.rollCategory();
    assert(category == 0);
    qa_pair = game.pickQuestionFromCategory(category);

    correct = game.submitAnswerForGUI("WrongAnswer");
    assert(correct == false);
    assert(game.getScore() == 1); // Score should not change
    assert(game.getLives() == 2); // Lives should decrease

    std::cout << "    ...PASSED" << std::endl;
}


void GameSetupTest::runTests() {
    std::cout << "--- Running GameSetup Tests ---" << std::endl;
    TestInitializationAndState();
    TestGameplayLoopStateChanges();
    std::cout << "--- All GameSetup Tests Passed ---\n" << std::endl;
}
