#include "pch.h"
#include "FileReaderTest.h"

// Helper function to find a question/answer by ID
std::pair<std::string, std::string> getRowById(const std::string& filename, int rowID) {
    std::ifstream file(filename);
    if (!file.is_open()) return { "", "" };

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, question, answer;
        if (std::getline(ss, id_str, ',') && std::getline(ss, question, ',') && std::getline(ss, answer, ',')) {
            try {
                if (std::stoi(id_str) == rowID) {
                    return { question, answer };
                }
            }
            catch (...) {
                // Ignore conversion errors
            }
        }
    }
    return { "Not Found", "Not Found" };
}


void FileReaderTest::Test3_ReadQuestionsAndAnswers() {
    std::cout << "\n--- Test 3: Reading All Questions and Answers ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    std::cout << "\nCalling FileReader::readQuestions() and FileReader::readAnswers()...\n";
    auto questions = FileReader::readQuestions(testFile);
    auto answers = FileReader::readAnswers(testFile);

    std::cout << "\n--- Data Read into Vectors ---\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        // To handle cases where answer might have been trimmed, check vector bounds
        if (i < answers.size()) {
            std::cout << "Q: " << questions[i] << " | A: " << answers[i] << std::endl;
        }
    }
    std::cout << "------------------------------\n";
    std::cout << "Total items read: " << questions.size() << std::endl;
    std::cout << "--- End of Test ---\n";
}

void FileReaderTest::Test4_ReadSpecificRow() {
    std::cout << "\n--- Test 4: Reading a Specific Question and Answer ---\n";
    const std::string testFile = "TestData.csv";
    TestHelpers::resetTestDataFile();
    TestHelpers::displayFileContent(testFile);

    int idToRead = 0;
    std::cout << "Enter the ID of the row to read (e.g., 3): ";
    std::cin >> idToRead;
    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> idToRead;
    }

    std::pair<std::string, std::string> result = getRowById(testFile, idToRead);

    std::cout << "\n--- Data Read for ID " << idToRead << " ---\n";
    std::cout << "Question: " << result.first << std::endl;
    std::cout << "Answer:   " << result.second << std::endl;
    std::cout << "----------------------------\n";
    std::cout << "--- End of Test ---\n";
}
