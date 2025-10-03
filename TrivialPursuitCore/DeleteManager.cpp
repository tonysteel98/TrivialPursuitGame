#include "pch.h"
#include "DeleteManager.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

bool DeleteManager::deleteRow(const std::string& filename, int rowID) {
    std::ifstream infile(filename);
    if (!infile.is_open()) return false;

    std::string line;
    std::vector<std::string> rows;

    // keep header
    if (std::getline(infile, line)) rows.push_back(line);

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string id;
        std::getline(ss, id, ',');
        if (std::stoi(id) != rowID) {
            rows.push_back(line);
        }
    }
    infile.close();

    std::ofstream outfile(filename, std::ios::trunc);
    if (!outfile.is_open()) return false;

    for (auto& row : rows) {
        outfile << row << "\n";
    }
    return true;
}
