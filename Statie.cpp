#include "Statie.hpp"
#include <iostream>

Statie::Statie(const std::string& nume)
    : nume(nume) {}

const std::string& Statie::getNume() const {
    return nume;
}

void Statie::adaugaRuta(const std::string& numeRuta) {
    rute.push_back(numeRuta);
}

void Statie::afiseaza() const {
    std::cout << "Statie: " << nume << "\n";
    std::cout << "Rute disponibile: ";
    for (const auto& r : rute) {
        std::cout << r << " ";
    }
    std::cout << "\n";
}
