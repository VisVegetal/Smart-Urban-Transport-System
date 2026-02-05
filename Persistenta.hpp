#ifndef PERSISTENTA_HPP
#define PERSISTENTA_HPP

#include <string>

class Dispecerat;

class Persistenta {
public:
    // ===================== STARE SISTEM =====================
    static void salveaza(
        const Dispecerat& d,
        const std::string& numeFisier
    );

    static void incarca(
        Dispecerat& d,
        const std::string& numeFisier
    );

    // ===================== VALIDARI =====================
    static bool fisierValid(
        const std::string& numeFisier
    );

    // ===================== RAPOARTE =====================
    static void salveazaRaport(
        const Dispecerat& d,
        const std::string& numeFisier
    );
};

#endif // PERSISTENTA_HPP
