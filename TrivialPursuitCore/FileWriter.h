#pragma once
#include <string>
#include <vector>

class FileWriter {
public:
    // Adds a single question, now with an internal duplicate check
    bool addQuestion(const std::string& filename, const std::string& question, const std::string& answer);

    // New function to parse and add multiple questions from strings
    // Returns true if all are added, false if counts mismatch or any fail to add
    bool addMultipleFromStrings(const std::string& filename, const std::string& questions, const std::string& answers);
};