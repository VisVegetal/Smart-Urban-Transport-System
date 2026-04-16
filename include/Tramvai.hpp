#ifndef TRAMVAI_HPP
#define TRAMVAI_HPP

#include "Vehicul.hpp"

class Tramvai : public Vehicul {
private:
    int numarSemafoare; // numarul de semafoare pe traseu
    bool prioritateIntersectii; // indica prioritatea in intersectii

public:
    Tramvai(int id,
            int capacitate,
            int numarSemafoare = 8,
            bool prioritateIntersectii = false);

    [[nodiscard]] double calculeazaTimp(const Ruta& ruta) const override;
    [[nodiscard]] std::string getTip() const override;

    // descriere generica
    [[nodiscard]] std::string descriere() const override;

    [[nodiscard]] int getNumarSemafoare() const;
    [[nodiscard]] bool arePrioritate() const;

    [[nodiscard]] Tramvai* clone() const override;
};

#endif
