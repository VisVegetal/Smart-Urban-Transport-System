#ifndef RUTA_HPP
#define RUTA_HPP

#include <string>
#include "Exceptii.hpp"

class Ruta {
private:
    std::string nume;
    double distanta;

public:
    Ruta(const std::string& nume, double distanta)
        : nume(nume), distanta(distanta) {
        if (distanta <= 0) {
            throw ValoareInvalidaException("Distanta invalida.");
        }
    }

    const std::string& getNume() const { return nume; }
    double getDistanta() const { return distanta; }
};

#endif
