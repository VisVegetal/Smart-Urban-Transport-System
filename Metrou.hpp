#ifndef METROU_HPP
#define METROU_HPP
#include "Vehicul.hpp"

class Metrou : public Vehicul {
public:
    Metrou(int id, int capacitate);
    double calculeazaTimp(const Ruta& ruta) const override;
    Vehicul* clone() const override;
    std::string getTip() const override;
};
#endif
