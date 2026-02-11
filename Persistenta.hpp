#ifndef PERSISTENTA_HPP
#define PERSISTENTA_HPP

#include <string>
#include "Dispecerat.hpp"

class Persistenta {
public:
    static void salveazaSistem(const Dispecerat& d, const std::string& numeFisier);

    static void incarcaSistem(Dispecerat& d, const std::string& numeFisier);

    static bool esteFisierValid(const std::string& numeFisier);

    static void creeazaBackup(const std::string& sursa, const std::string& destinatie);
};

#endif