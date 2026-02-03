#ifndef TRAMVAI_HPP
#define TRAMVAI_HPP
#include "Vehicul.hpp"

class Tramvai : public Vehicul {
public:
    Tramvai(int id, int capacitate);
    double calculeazaTimp(const Ruta& ruta) const override;
    Vehicul* clone() const override;
    std::string getTip() const override;
};
#endif
