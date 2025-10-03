#pragma once
#include <string>
#include <vector>

class FileReader {
public:
    // Reads questions (column 2 of CSVs like Geography.csv)
    static std::vector<std::string> readQuestions(const std::string& filename);

    // Reads answers (column 3 of CSVs like Geography.csv)
    static std::vector<std::string> readAnswers(const std::string& filename);

    // Reads high scores (returns vector of {player, score})
    static std::vector<std::pair<std::string, int>> readHighScores(const std::string& filename);
};
