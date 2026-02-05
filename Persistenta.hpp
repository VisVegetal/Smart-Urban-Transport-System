#ifndef PERSISTENTA_HPP
#define PERSISTENTA_HPP

#include <string>
#include "Dispecerat.hpp"

class Persistenta {
public:
    static void salveaza(const Dispecerat& d, const std::string& numeFisier);
    static void incarca(Dispecerat& d, const std::string& numeFisier);
};

#endif // PERSISTENTA_HPP
