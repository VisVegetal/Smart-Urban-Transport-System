#include "Logger.hpp"
#include <iostream>
#include <fstream>

std::vector<std::string> Logger::logs;

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "[INFO]";
        case LogLevel::WARNING: return "[WARNING]";
        case LogLevel::ERROR: return "[ERROR]";
        default: return "[UNKNOWN]";
    }
}

void Logger::log(LogLevel level, const std::string& mesaj) {
    std::string linie = levelToString(level) + " " + mesaj;
    logs.push_back(linie);
}

void Logger::afiseazaLoguri() {
    for (const auto& l : logs) {
        std::cout << l << "\n";
    }
}

void Logger::salveazaInFisier(const std::string& numeFisier) {
    std::ofstream fout(numeFisier);
    for (const auto& l : logs) {
        fout << l << "\n";
    }
}
