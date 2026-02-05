#ifndef STATISTICI_HPP
#define STATISTICI_HPP

#include <string>
#include "Dispecerat.hpp"

class Statistici {
public:
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
