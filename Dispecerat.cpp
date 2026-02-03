#include "Dispecerat.hpp"
#include <iostream>
#include <algorithm>

Dispecerat::Dispecerat() = default;

Dispecerat::~Dispecerat() {
    elibereazaMemorie();
}

void Dispecerat::elibereazaMemorie() {
    for (auto v : vehicule) {
        delete v;
    }
    vehicule.clear();
}

Dispecerat::Dispecerat(const Dispecerat& other) {
    for (const auto v : other.vehicule) {
        vehicule.push_back(v->clone());
    }
}

Dispecerat& Dispecerat::operator=(Dispecerat other) {
    std::swap(vehicule, other.vehicule);
    return *this;
}

void Dispecerat::adaugaVehicul(const Vehicul& v) {
    vehicule.push_back(v.clone());
}

void Dispecerat::afiseazaVehicule() const {
    for (const auto v : vehicule) {
        std::cout << v->getTip()
                  << " | ID: " << v->getId()
                  << " | Capacitate: " << v->getCapacitate()
                  << "\n";
    }
}

double Dispecerat::calculeazaTimpTotal(const Ruta& ruta) const {
    double timpTotal = 0.0;

    for (const auto v : vehicule) {
        timpTotal += v->calculeazaTimp(ruta);

        if (dynamic_cast<const Metrou*>(v)) {
            timpTotal *= 0.98;
        }
    }

    return timpTotal;
}
