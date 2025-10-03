#include "pch.h"
#include "DeleteManagerTest.h"
#include "FileReaderTest.h"
#include "FileWriterTest.h"
#include "GameFunctionsTest.h"
#include "GameSetupTest.h"

void display_menu() {
    std::cout << "\n=======================================================\n";
    std::cout << "      TRIVIAL PURSUIT - INTERACTIVE TEST SUITE\n";
    std::cout << "=======================================================\n";
    std::cout << "--- DeleteManager Tests ---\n";
    std::cout << " 1. Delete an existing row from TestData.csv\n";
    std::cout << " 2. Attempt to delete a non-existent row from TestData.csv\n";
    std::cout << "\n--- FileReader Tests ---\n";
    std::cout << " 3. Read questions and answers from TestData.csv\n";
    std::cout << " 4. Read question and answer from a specific row in TestData.csv\n";
    std::cout << "\n--- FileWriter Tests ---\n";
    std::cout << " 5. Add a single question and answer to TestData.csv\n";
    std::cout << " 6. Add multiple questions and answers (batch mode) to TestData.csv\n";
    std::cout << "\n--- GameFunctions Tests ---\n";
    std::cout << " 7. Interactive dice roller\n";
    std::cout << " 8. Interactive answer checker (case-sensitive)\n";
    std::cout << "\n--- GameSetup Tests ---\n";
    std::cout << " 9. Simulate a mini-game round (questions from TestData.csv)\n";
    std::cout << " 10. Demonstrate game over conditions\n";
    std::cout << "\n 11. Exit\n";
    std::cout << "=======================================================\n";
    std::cout << "Enter your choice: ";
}

int main() {
    DeleteManagerTest deleteTest;
    FileReaderTest readTest;
    FileWriterTest writeTest;
    GameFunctionsTest funcTest;
    GameSetupTest setupTest;

    int choice = 0;
    while (true) {
        display_menu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\n*** Invalid input. Please enter a number. ***\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: deleteTest.Test1_InteractiveDeletion(); break;
        case 2: deleteTest.Test2_InteractiveNonExistentDeletion(); break;
        case 3: readTest.Test3_ReadQuestionsAndAnswers(); break;
        case 4: readTest.Test4_ReadSpecificRow(); break;
        case 5: writeTest.Test5_AddSingleQuestion(); break;
        case 6: writeTest.Test6_AddMultipleQuestions(); break;
        case 7: funcTest.Test7_InteractiveDiceRoll(); break;
        case 8: funcTest.Test8_InteractiveAnswerChecker(); break;
        case 9: setupTest.Test9_MiniGameRound(); break;
        case 10: setupTest.Test10_CheckGameOverState(); break;
        case 11:
            std::cout << "Exiting test suite.\n";
            return 0;
        default:
            std::cout << "\n*** Invalid choice. Please try again. ***\n";
            break;
        }

        // Pause and wait for user to press Enter before showing the menu again
        std::cout << "\nPress Enter to continue...";
        // Clear remaining buffer from previous input before waiting for new input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    return 0;
}
