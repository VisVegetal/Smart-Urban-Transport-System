#include "Logger.hpp"
#include <iostream>
#include <fstream>
#include "Exceptii.hpp"

std::vector<std::string> Logger::logs;

// converteste nivelul de log intr-un format text
std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:    return "[INFO]";
        case LogLevel::WARNING: return "[WARNING]";
        case LogLevel::ERROR:   return "[ERROR]";
        default:                return "[UNKNOWN]";
    }
}

// adauga un mesaj de log in lista interna
void Logger::log(LogLevel level, const std::string& mesaj) {
    std::string linie = levelToString(level) + " " + mesaj;
    logs.push_back(linie);
}

// afiseaza toate mesajele de log
void Logger::afiseazaLoguri() {
    if (logs.empty()) {
        std::cout << "Nu exista loguri.\n";
        return;
    }

    for (const auto& l : logs) {
        std::cout << l << "\n";
    }
}

// salveaza logurile intr-un fisier text
void Logger::salveazaInFisier(const std::string& numeFisier) {
    std::ofstream fout(numeFisier);
    if (!fout) {
        throw TransportException("Nu se poate deschide fisierul de log.");
    }

    for (const auto& l : logs) {
        fout << l << "\n";
    }
}
