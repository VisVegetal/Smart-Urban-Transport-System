#ifndef STATISTICI_HPP
#define STATISTICI_HPP

#include <string>
#include "Dispecerat.hpp"

class Statistici {
public:
    static void distributieVehicule(const Dispecerat& d);
    static double impactMediuIncident(const Dispecerat& d);
    static void raportDetaliat(const Dispecerat& d);

    static const Vehicul* vehiculCelMaiRapid(
        const Dispecerat& d,
        const std::string& numeRuta
    );

    static const Vehicul* vehiculCapacitateMaxima(
        const Dispecerat& d
    );

    static double timpMediuPeRuta(
        const Dispecerat& d,
        const std::string& numeRuta
    );

    static void raportGeneral(const Dispecerat& d);
};

#endif
