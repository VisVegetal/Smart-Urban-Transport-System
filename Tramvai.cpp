#include "Tramvai.hpp"

Tramvai::Tramvai(int id, int capacitate) {
    :Vehicul(id, capacitate);
}

double Tramvai::calculeazaTimp(const Ruta& ruta) const {
    return ruta.getDistanta() / VITEZA_MEDIE;
}

Vehicul *Tramvai::clone() const {
    return new Tramvai(*this);
}

std::string Tramvai::getTipos() const {
    return "Tramvai";
}




