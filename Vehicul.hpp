#ifndef VEHICUL_HPP
#define VEHICUL_HPP

#include <string>
#include "Ruta.hpp"

class Vehicul {
protected:
    int id; //identificator unic al vehiculului
    int capacitate; // capacitatea maxima de pasageri
    static int numarVehicule; // numarul total de vehicule create

public:
    Vehicul(int id, int capacitate);
    virtual ~Vehicul();

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getCapacitate() const;

    [[nodiscard]] virtual double calculeazaTimp(const Ruta& ruta) const = 0; //timpul de parcurgere a unei rute
    [[nodiscard]] virtual Vehicul* clone() const = 0;
    [[nodiscard]] virtual std::string getTip() const = 0;

    static int getNumarVehicule();
};

#endif
