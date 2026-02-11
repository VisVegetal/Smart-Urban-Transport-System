#ifndef RUTA_HPP
#define RUTA_HPP

#include <string>
#include <utility>
#include "Exceptii.hpp"

class Ruta {
private:
    std::string nume;
    double distanta; //in km

public:
    Ruta(const std::string&  nume, double distanta)
        : nume(nume), distanta(distanta) {
        if (distanta <= 0) {
            throw ValoareInvalidaException("Distanta invalida.");
        }
    }

    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] double getDistanta() const { return distanta; }
};


#endif
