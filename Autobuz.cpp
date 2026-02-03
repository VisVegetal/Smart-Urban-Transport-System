#include "Autobuz.hpp"

Autobuz::Autobuz(int id, int capacitate)
    : Vehicul(id, capacitate) {}

double Autobuz::calculeazaTimp(const Ruta& ruta) const {
    return ruta.getDistanta() / 30.0;
}

Vehicul* Autobuz::clone() const {
    return new Autobuz(*this);
}

std::string Autobuz::getTip() const {
    return "Autobuz";
}
