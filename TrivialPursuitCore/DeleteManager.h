#pragma once
#include <string>

class DeleteManager {
public:
    bool deleteRow(const std::string& filename, int rowID);
};
