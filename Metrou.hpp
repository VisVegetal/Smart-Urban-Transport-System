#ifndef METROU_HPP
#define METROU_HPP

#include "Vehicul.hpp"

class Metrou : public Vehicul {
private:
    int intervalMinute; //intervalul dintre metrouri
    bool sistemAutomat; // indica daca sistemul de control al metroului este automat sau manual

public:
    Metrou(int id,
           int capacitate,
           int intervalMinute = 4,
           bool sistemAutomat = true);

    [[nodiscard]] double calculeazaTimp(const Ruta& ruta) const override;

    [[nodiscard]] int getIntervalMinute() const;
    [[nodiscard]] bool esteAutomat() const;
    [[nodiscard]] std::string getTip() const override;


    [[nodiscard]] Metrou* clone() const override;
};

#endif
