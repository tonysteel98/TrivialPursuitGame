#include "pch.h"
#include "TestHelpers.h"
#include <fstream>
#include <iostream>
#include <vector>

void TestHelpers::resetTestDataFile() {
    std::ofstream outfile("TestData.csv", std::ios::trunc);
    outfile << "ID,Question,Answer\n";
    outfile << "1,What is the capital of France?,Paris\n";
    outfile << "2,Who wrote 'Hamlet'?,Shakespeare\n";
    outfile << "3,What is the chemical symbol for water?,H2O\n";
    outfile << "4,In which year did the Titanic sink?,1912\n";
    outfile.close();
}

void TestHelpers::resetCategoryFiles() {
    // These files are required for the GameSetup class to initialize correctly.
    const std::vector<std::string> categories = { "geography.csv", "history.csv", "science.csv" };

    std::ofstream geo("geography.csv", std::ios::trunc);
    geo << "ID,Question,Answer\n";
    geo << "1,What is the largest desert in the world?,Antarctic Polar Desert\n";
    geo.close();

    std::ofstream hist("history.csv", std::ios::trunc);
    hist << "ID,Question,Answer\n";
    hist << "1,Who was the first person to step on the moon?,Neil Armstrong\n";
    hist.close();

    std::ofstream sci("science.csv", std::ios::trunc);
    sci << "ID,Question,Answer\n";
    sci << "1,What is the powerhouse of the cell?,Mitochondria\n";
    sci.close();

    // Create empty files for the other categories to prevent file-not-found errors.
    const std::vector<std::string> otherFiles = { "sports.csv", "movie.csv", "custom.csv" };
    for (const auto& file : otherFiles) {
        std::ofstream emptyFile(file, std::ios::trunc);
        emptyFile << "ID,Question,Answer\n";
        emptyFile.close();
    }
}

void TestHelpers::displayFileContent(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "\n[ERROR: Could not open " << filename << " to display content. Please ensure the file exists.]\n";
        return;
    }
    std::cout << "\n--- Current Content of " << filename << " ---\n";
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "---------------------------------------\n";
    infile.close();
}

