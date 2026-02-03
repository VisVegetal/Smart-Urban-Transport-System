#include "Metrou.hpp"

Metrou::Metrou(int id, int capacitate)
    : Vehicul(id, capacitate) {}

double Metrou::calculeazaTimp(const Ruta &ruta) const {
    return ruta.getDistanta() / VITEZA_MEDIE;
}

Vehicul* Metrou::clone() const {
    return new Metrou(*this);
}

std::string Metrou::getTip() const {
    return "Metrou";
}



