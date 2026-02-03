#ifndef AUTOBUZ_HPP
#define AUTOBUZ_HPP

#include "Vehicul.hpp"
#include "Ruta.hpp"

class Autobuz : public Vehicul {
private:
    static constexpr double VITEZA_MEDIE = 30.0;
public:
    Autobuz(int id, int capacitate);
    double calculezaTimp(const Ruta& ruta) const override;
    Vehicul* clone() const override;
    std::string getTip() const override;
};

#endif