#ifndef VEHICUL_HPP
#define VEHICUL_HPP

#include <string>
#include "Ruta.hpp"

class Vehicul {
protected:
    int id;
    int capacitate;
    static int numarVehicule;

public:
    Vehicul(int id, int capacitate);
    virtual ~Vehicul() = default;

    int getId() const;
    int getCapacitate() const;

    virtual double calculeazaTimp(const Ruta& ruta) const = 0;
    virtual Vehicul* clone() const = 0;
    virtual std::string getTip() const = 0;

    static int getNumarVehicule();
};

#endif
