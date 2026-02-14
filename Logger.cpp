#include "Logger.hpp"
#include <fstream>
#include <iostream>

void Logger::afiseazaLoguri() const {
    if (loguri.empty()) {
        std::cout << "Nu exista loguri inregistrate.\n";
        return;
    }
    for (const auto& l : loguri) {
        std::cout << l << "\n";
    }
}

void Logger::salveazaInFisier(const std::string& numeFisier) const {
    std::ofstream fout(numeFisier);
    if (!fout) {
        std::cerr << "Eroare la deschiderea fisierului de loguri: " << numeFisier << "\n";
        return;
    }
    for (const auto& l : loguri) {
        fout << l << "\n";
    }
    fout.close();
    std::cout << "Logurile au fost salvate cu succes in: " << numeFisier << "\n";
}