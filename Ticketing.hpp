#ifndef TICKETING_HPP
#define TICKETING_HPP

#include <vector>
#include <memory>
#include "Bilet.hpp"

class SistemTicketing {
private:
    std::vector<std::unique_ptr<Bilet>> bileteVandute;
    double venitTotal;
    int contorSerie;

public:
    SistemTicketing();
    ~SistemTicketing() = default;

    void emiteBiletIntreg(double pret);
    void emiteBiletRedus(double pret, double reducere);
    
    [[nodiscard]] double calculeazaVenituri() const;
    void afiseazaIstoric() const;
    void anuleazaUltimulBilet();
    void curataIstoric();
};

#endif