#include "Autobuz.hpp"

Autobuz::Autobuz(int id, int capacitate, bool banda, int opriri, int semafoare)
    : Vehicul(id, capacitate),
      bandaDedicata(banda),
      numarOpriri(opriri),
      numarSemafoare(semafoare) {}

double Autobuz::calculeazaTimp(const Ruta& ruta) const {
    double viteza = 30.0; // km/h
    double timp = ruta.getDistanta() / viteza; // in ore

    // intarzieri cauzate de opriri
    timp += numarOpriri * 0.01;

    // intarzieri cauzare de semafoare
    timp += numarSemafoare * 0.015;

    // intarzieri din cauza traficului in cazul in care banda dedicata nu exista
    if (!bandaDedicata) {
        timp *= 1.2;
    }

    return timp;
}

bool Autobuz::areBandaDedicata() const {
    return bandaDedicata;
}

int Autobuz::getNumarOpriri() const {
    return numarOpriri;
}

int Autobuz::getNumarSemafoare() const {
    return numarSemafoare;
}

std::string Autobuz::getTip() const {
    return "Autobuz";
}

// descriere generica
std::string Autobuz::descriere() const {
    return "Autobuz | ID " + std::to_string(id) +
           " | Capacitate " + std::to_string(capacitate);
}

Autobuz* Autobuz::clone() const {
    return new Autobuz(*this);
}
