#include "Autobuz.hpp"

Autobuz::Autobuz(int id, int capacitate)
    : Vehicul(id, capacitate) {}

double Autobuz::calculeazaTimp(const Ruta& ruta) const {
    // timp = distanta / viteza (ore)
    return ruta.getDistanta() / VITEZA_MEDIE;
}

Vehicul* Autobuz::clone() const {
    return new Autobuz(*this);
}

std::string Autobuz::getTip() const {
    return "Autobuz";
}
