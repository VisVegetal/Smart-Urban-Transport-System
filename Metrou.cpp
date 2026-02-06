#include "Metrou.hpp"

Metrou::Metrou(int id, int capacitate, int interval, bool automat)
    : Vehicul(id, capacitate),
      intervalMinute(interval),
      sistemAutomat(automat) {}

double Metrou::calculeazaTimp(const Ruta& ruta) const {
    double viteza = 60.0;
    double timp = ruta.getDistanta() / viteza;

    // timp de așteptare mediu
    timp += (intervalMinute / 60.0) / 2.0;

    //sistemul automat este mai eficient
    if (sistemAutomat) {
        timp *= 0.95;
    }

    return timp;
}

int Metrou::getIntervalMinute() const {
    return intervalMinute;
}

bool Metrou::esteAutomat() const {
    return sistemAutomat;
}

std::string Metrou::getTip() const {
    return "Metrou";
}

Metrou* Metrou::clone() const {
    return new Metrou(*this);
}