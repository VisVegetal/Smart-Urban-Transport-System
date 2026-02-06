#include "Statie.hpp"
#include <iostream>
#include "Exceptii.hpp"

Statie::Statie(const std::string& nume)
    : nume(nume) {

    if (nume.empty()) {
        throw ValoareInvalidaException("Nume statie invalid.");
    }
}

const std::string& Statie::getNume() const {
    return nume;
}

// adauga o ruta in lista statiei
void Statie::adaugaRuta(const std::string& numeRuta) {
    for (const auto& r : rute) {
        if (r == numeRuta) {
            return; // ruta deja exista
        }
    }
    rute.push_back(numeRuta);
}

// afiseaza statia si rutele asociate
void Statie::afiseaza() const {
    std::cout << "Statie: " << nume << "\n";
    std::cout << "Rute disponibile: ";

    if (rute.empty()) {
        std::cout << "Niciuna";
    } else {
        for (const auto& r : rute) {
            std::cout << r << " ";
        }
    }

    std::cout << "\n";
}
