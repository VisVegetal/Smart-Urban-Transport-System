#include "Vehicul.hpp"
#include "Exceptii.hpp"

int Vehicul::numarVehicule = 0;

Vehicul::Vehicul(int id, int capacitate)
    : id(id), capacitate(capacitate) {
    if (capacitate <= 0) {
        throw VehiculException("Capacitate invalida, trebuie sa fie pozitiva.");
    }
    ++numarVehicule;
}

Vehicul::~Vehicul(){
    --numarVehicule;
}

int Vehicul::getId() const { return id; }
int Vehicul::getCapacitate() const { return capacitate; }

double Vehicul::calculeazaVenitEstimativ() const {
    // Grad ocupare mediu 60% si bilet 3.5 RON
    return (this->capacitate * 0.6) * 3.5;
}

int Vehicul::getNumarVehicule() { return numarVehicule; }