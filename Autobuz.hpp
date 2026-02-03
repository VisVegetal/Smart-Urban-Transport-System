#ifndef AUTOBUZ_HPP
#define AUTOBUZ_HPP
#include "Vehicul.hpp"

class Autobuz : public Vehicul {
public:
    Autobuz(int id, int capacitate);
    double calculeazaTimp(const Ruta& ruta) const override;
    Vehicul* clone() const override;
    std::string getTip() const override;
};
#endif
