#ifndef METROU_HPP
#define METROU_HPP

#include "Vehicul.hpp"
#include "Ruta.hpp"

class Metrou : public Vehicul {
private:
    static constexpr double VITEZA_MEDIE = 60.0

public:
    Metrou (int id, int capacitate);
    double calculeazaTimp(const Ruta &ruta) const override;
    Vehicul * clone() const override;
    std::string getTip() const override;
};

#endif