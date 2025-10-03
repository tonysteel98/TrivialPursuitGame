#pragma once
#include <string>

// Provides static helper functions for the test suite.
class TestHelpers {
public:
    // Resets the main TestData.csv to its original, default state.
    static void resetTestDataFile();

    // Creates dummy category files needed for GameSetup tests.
    static void resetCategoryFiles();

    // Displays the entire content of a given file to the console.
    static void displayFileContent(const std::string& filename);
};

