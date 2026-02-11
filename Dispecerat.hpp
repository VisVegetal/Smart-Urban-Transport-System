#ifndef DISPECERAT_HPP
#define DISPECERAT_HPP

#include <vector>
#include <string>

#include "Vehicul.hpp"
#include "Ruta.hpp"
#include "Incident.hpp"
#include "Mentenanta.hpp"   // NOU: trebuie inclus
#include "Ticketing.hpp"    // NOU: trebuie inclus

class Dispecerat {
private:
    std::vector<Vehicul*> vehicule;
    std::vector<Ruta> rute;
    std::vector<Incident> incidente;

    // AICI ERA PROBLEMA: Trebuie declarate ca membri ai clasei
    Mentenanta managementTehnic;
    SistemTicketing sistemTicketing;

    void elibereazaMemorie();

public:
    Dispecerat();
    ~Dispecerat() noexcept;
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
    int calculeazaImpactTotal() const;

    double simuleazaCursa(int idVehicul, const std::string& numeRuta);
    double calculeazaTimpTotal(const std::string& numeRuta) const;

    void vindeBilet(bool redus, double pret, double reducere = 0.0);
    double calculeazaVenituriTotale() const;
    void sorteazaVehiculeDupaCapacitate();
    void filtreazaVehiculeDupaTip(const std::string& tip) const;

    Mentenanta& getMentenanta();
    SistemTicketing& getTicketing();

    int numarVehicule() const;
    int numarIncidente() const;
    const std::vector<Vehicul*>& getVehicule() const;
    const std::vector<Ruta>& getRute() const;
    const std::vector<Incident>& getIncidente() const;
    void afiseazaIncidente() const;

    bool existaRuta(const std::string& nume) const;
    void stergeRuta(const std::string& nume);

    Mentenanta& getManagementTehnic();
    SistemTicketing& getSistemTicketing();

};

#endif