#ifndef BILET_HPP
#define BILET_HPP

#include <string>

class Bilet {
private:
    std::string tip; // "Adult", "Elev", "Pensionar"
    double pret;
public:
    Bilet(std::string tip, double pret) : tip(tip), pret(pret) {}
    double getPret() const { return pret; }
    std::string getTip() const { return tip; }
};

#endif