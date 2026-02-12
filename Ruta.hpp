#ifndef RUTA_HPP
#define RUTA_HPP

#include <string>

class Ruta {
private:
    std::string nume;
    double distanta;

public:
    Ruta() : distanta(0.0) {}
    Ruta(std::string nume, double distanta);

    [[nodiscard]] const std::string getNume() const { return nume; }
    [[nodiscard]] double getDistanta() const { return distanta; }
};

#endif