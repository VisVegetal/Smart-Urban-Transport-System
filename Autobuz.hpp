#ifndef AUTOBUZ_HPP
#define AUTOBUZ_HPP

#include "Vehicul.hpp"

class Autobuz : public Vehicul {
private:
    bool bandaDedicata; // indica daca autobuzul are banda dedicata sau nu
    int numarOpriri; //numar opriri pe ruta
    int numarSemafoare; // numar semafoare pe ruta

public:
    Autobuz(int id,
            int capacitate,
            bool bandaDedicata = false,
            int numarOpriri = 10,
            int numarSemafoare = 12);

    //timpul tinand cont de semafoare, opriri
    [[nodiscard]] double calculeazaTimp(const Ruta& ruta) const override;

    [[nodiscard]] bool areBandaDedicata() const;
    [[nodiscard]] int getNumarOpriri() const;
    [[nodiscard]] int getNumarSemafoare() const;

    [[nodiscard]] std::string getTip() const override;

    // descriere generica
    [[nodiscard]] std::string descriere() const override;

    [[nodiscard]] Autobuz* clone() const override;
};

#endif
