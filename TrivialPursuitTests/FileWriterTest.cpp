#include "pch.h"
#include "FileWriterTest.h"

void FileWriterTest::Test5_AddSingleQuestion() {
    std::cout << "\n--- Test 5: Add a Single Question ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    std::string question, answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer before getline
    std::cout << "Enter a new question to add: ";
    std::getline(std::cin, question);
    std::cout << "Enter the answer: ";
    std::getline(std::cin, answer);

    FileWriter fw;
    if (fw.addQuestion(testFile, question, answer)) {
        std::cout << "\nSuccessfully added the new question. A new ID should be assigned.\n";
    }
    else {
        std::cout << "\nFailed to add question. It might be a duplicate or empty.\n";
    }

    TestHelpers::displayFileContent(testFile);
    std::cout << "--- End of Test ---\n";
}

void FileWriterTest::Test6_AddMultipleQuestions() {
    std::cout << "\n--- Test 6: Add Multiple Questions (use ';;' as separator) ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    std::string questions, answers;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    std::cout << "Example Questions: What is 2+2?;;What is the color of the sky?\n";
    std::cout << "Enter questions separated by ';;': ";
    std::getline(std::cin, questions);

    std::cout << "Example Answers: 4;;Blue\n";
    std::cout << "Enter corresponding answers separated by ';;': ";
    std::getline(std::cin, answers);

    FileWriter fw;
    if (fw.addMultipleFromStrings(testFile, questions, answers)) {
        std::cout << "\nSuccessfully added the batch of questions.\n";
    }
    else {
        std::cout << "\nFailed to add batch. Check for duplicates or mismatched counts.\n";
    }
    TestHelpers::displayFileContent(testFile);
    std::cout << "--- End of Test ---\n";
}
