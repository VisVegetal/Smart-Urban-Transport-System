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
    virtual ~Vehicul(); // Implementat în cpp pentru decrementare static

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getCapacitate() const;

    // metoda virtuala pentru calcul timp
    [[nodiscard]] virtual double calculeazaTimp(const Ruta& ruta) const = 0;

    // tipul vehiculului
    [[nodiscard]] virtual std::string getTip() const = 0;

    // descriere generica
    [[nodiscard]] virtual std::string descriere() const = 0;

    // clona polimorfica
    [[nodiscard]] virtual Vehicul* clone() const = 0;

    // calcul venituri sistem bilete
    [[nodiscard]] virtual double calculeazaVenitEstimativ() const;

    static int getNumarVehicule();
};

#endif