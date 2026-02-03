#include "Vehicul.hpp"
#include "Exceptii.hpp"

int Vehicul::numarVehicule = 0;

Vehicul::Vehicul(int id, int capacitate)
    : id(id), capacitate(capacitate) {
    if (capacitate <= 0) {
        throw VehiculException("Capacitate invalida.");
    }
    ++numarVehicule;
}

int Vehicul::getId() const { return id; }
int Vehicul::getCapacitate() const { return capacitate; }

int Vehicul::getNumarVehicule() {
    return numarVehicule;
}
