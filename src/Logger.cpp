#include "../include/Logger.hpp"

#include <fstream>
#include <iostream>

void Logger::showLogs() const {
    if (logs.empty()) {
        std::cout << "No logs recorded.\n";
        return;
    }
    for (const auto& l : logs) {
        std::cout << l << "\n";
    }
}

void Logger::saveToFile(const std::string& fileName) const {
    std::ofstream fout(fileName);
    if (!fout) {
        std::cerr << "Error opening log file: " << fileName << "\n";
        return;
    }
    for (const auto& l : logs) {
        fout << l << "\n";
    }
    fout.close();
    std::cout << "Logs saved successfully to: " << fileName << "\n";
}
