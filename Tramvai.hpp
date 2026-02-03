#ifndef TRAMVAI_HPP
#define TRAMVAI_HPP

#include "Vehicul.hpp"

class Tramvai : public Vehicul {
private:
    static constexpr double VITEZA_MEDIE = 40.0;
public:
    Tramvai(int id, int capacitate);

    double calculeazaTimp(const Ruta &ruta) const override;
    Vehicul *clone() const override;
    std::string getTipos() const override;
};

#endif
