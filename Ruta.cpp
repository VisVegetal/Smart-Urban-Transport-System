#include "Ruta.hpp"
#include "Exceptii.hpp"
#include <cmath>

Ruta::Ruta() : nume("In asteptare"), distanta(0.0) {}

Ruta::Ruta(const std::string& nume, double distanta) : nume(nume), distanta(distanta) {
    if (distanta < 0) {
        throw ValoareInvalidaException("Distanta nu poate fi negativa.");
    }
}

Ruta::Ruta(const Ruta& other) {
    this->nume = other.nume;
    this->distanta = other.distanta;
}

Ruta& Ruta::operator=(const Ruta& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->distanta = other.distanta;
    }
    return *this;
}

const std::string& Ruta::getNume() const { return nume; }
double Ruta::getDistanta() const { return distanta; }

void Ruta::setNume(const std::string& numeNou) {
    if(!numeNou.empty()) this->nume = numeNou;
}

void Ruta::setDistanta(double distantaNoua) {
    if(distantaNoua >= 0) this->distanta = distantaNoua;
}

bool Ruta::operator==(const Ruta& other) const {
    return (this->nume == other.nume && std::abs(this->distanta - other.distanta) < 0.0001);
}

bool Ruta::operator!=(const Ruta& other) const {
    return !(*this == other);
}

bool Ruta::operator<(const Ruta& other) const {
    if (this->distanta != other.distanta) return this->distanta < other.distanta;
    return this->nume < other.nume;
}

bool Ruta::operator>(const Ruta& other) const {
    return other < *this;
}

std::ostream& operator<<(std::ostream& os, const Ruta& r) {
    os << "Ruta: " << r.nume << " (" << r.distanta << " km)";
    return os;
}