#ifndef DISPECERAT_HPP
#define DISPECERAT_HPP

#include <vector>
#include "Vehicul.hpp"
#include "Ruta.hpp"
#include "Incident.hpp"

class Dispecerat {
private:
    std::vector<Vehicul*> vehicule;

    void elibereazaMemorie();

public:
    Dispecerat();
    ~Dispecerat();

    Dispecerat(const Dispecerat& other);

    Dispecerat& operator=(Dispecerat other);

    void adaugaVehicul(const Vehicul& v);
    void afiseazaVehicule() const;

    double calculeazaTimpTotal(const Ruta& ruta) const;
};

#endif
