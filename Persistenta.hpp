#ifndef PERSISTENTA_HPP
#define PERSISTENTA_HPP

#include <string>

class Dispecerat;

class Persistenta {
public:
    //stare sistem
    static void salveaza(
        const Dispecerat& d,
        const std::string& numeFisier
    );

    static void incarca(
        Dispecerat& d,
        const std::string& numeFisier
    );

    //validari
    static bool fisierValid(
        const std::string& numeFisier
    );

    //rapoarte
    static void salveazaRaport(
        const Dispecerat& d,
        const std::string& numeFisier
    );
};

#endif 
