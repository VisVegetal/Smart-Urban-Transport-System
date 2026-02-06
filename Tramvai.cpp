#include "Tramvai.hpp"

Tramvai::Tramvai(int id, int capacitate, int semafoare, bool prioritate)
    : Vehicul(id, capacitate),
      numarSemafoare(semafoare),
      prioritateIntersectii(prioritate) {}

double Tramvai::calculeazaTimp(const Ruta& ruta) const {
    double viteza = 40.0; // km/h
    double timp = ruta.getDistanta() / viteza;

    if (prioritateIntersectii) {
        // intarzieri minime datorita prioritatii
        timp += numarSemafoare * 0.005;
    } else {
        // intarzieri mari fara prioritate
        timp += numarSemafoare * 0.02;
    }

    return timp;
}

int Tramvai::getNumarSemafoare() const {
    return numarSemafoare;
}

bool Tramvai::arePrioritate() const {
    return prioritateIntersectii;
}

Tramvai* Tramvai::clone() const {
    return new Tramvai(*this);
}

std::string Tramvai::getTip() const {
    return "Tramvai";
}
