#include "pch.h"
#include "DeleteManagerTest.h"

void DeleteManagerTest::Test1_InteractiveDeletion() {
    std::cout << "\n--- Test 1: Delete an Existing Row ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    int idToDelete = 0;
    std::cout << "Enter the ID of a row to delete (e.g., 2 for Shakespeare): ";
    std::cin >> idToDelete;
    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> idToDelete;
    }

    DeleteManager dm;
    if (dm.deleteRow(testFile, idToDelete)) {
        std::cout << "Successfully processed delete request for ID " << idToDelete << ".\n";
    }
    else {
        std::cout << "Function returned false. This could happen if file doesn't exist.\n";
    }

    TestHelpers::displayFileContent(testFile);
    std::cout << "--- End of Test ---\n";
}

void DeleteManagerTest::Test2_InteractiveNonExistentDeletion() {
    std::cout << "\n--- Test 2: Attempt to Delete a Non-Existent Row ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    int idToDelete = 0;
    std::cout << "Enter a non-existent ID to delete (e.g., 99): ";
    std::cin >> idToDelete;
    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> idToDelete;
    }

    DeleteManager dm;
    dm.deleteRow(testFile, idToDelete);
    std::cout << "Processed request. The file content should remain unchanged.\n";

    TestHelpers::displayFileContent(testFile);
    std::cout << "--- End of Test ---\n";
}
