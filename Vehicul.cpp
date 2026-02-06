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

// destructorul decrementeaza numarul total de vehicule
Vehicul::~Vehicul(){
    --numarVehicule;
}

// ID-ul vehiculului
int Vehicul::getId() const {
    return id;
}

// capacitatea vehiculului
int Vehicul::getCapacitate() const {
    return capacitate;
}

// numarul total de vehicule existente
int Vehicul::getNumarVehicule() {
    return numarVehicule;
}
