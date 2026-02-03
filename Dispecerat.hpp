#ifndef DISPECERAT_HPP
#define DISPECERAT_HPP

#include <vector>
#include <string>

#include "Vehicul.hpp"
#include "Ruta.hpp"
#include "Incident.hpp"
#include "Exceptii.hpp"

class Dispecerat {
private:
    std::vector<Vehicul*> vehicule;

    std::vector<Ruta> rute;

    std::vector<Incident> incidente;

    void elibereazaMemorie();

public:
    Dispecerat();
    ~Dispecerat();

    Dispecerat(const Dispecerat& other);

    Dispecerat& operator=(Dispecerat other);

    void adaugaVehicul(const Vehicul& v);
    bool existaVehicul(int id) const;
    void stergeVehicul(int id);
    void afiseazaVehicule() const;

    void adaugaRuta(const Ruta& ruta);
    void afiseazaRute() const;
    const Ruta* gasesteRuta(const std::string& nume) const;

    void adaugaIncident(const Incident& incident);
    void afiseazaIncidente() const;
    int calculeazaImpactTotal() const;

    double calculeazaTimpTotal(const std::string& numeRuta) const;
};

#endif
