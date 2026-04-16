#ifndef DISPECERAT_HPP
#define DISPECERAT_HPP

#include <vector>
#include <string>

#include "Vehicul.hpp"
#include "Ruta.hpp"
#include "Incident.hpp"
#include "Mentenanta.hpp"
#include "Ticketing.hpp"


class Dispecerat {
private:
    std::vector<Vehicul*> vehicule;
    std::vector<Ruta> rute;
    std::vector<Incident> incidente;

    Mentenanta managementTehnic;
    SistemTicketing sistemTicketing;

    void elibereazaMemorie();

public:
    Dispecerat();
    ~Dispecerat() noexcept;
    Dispecerat(const Dispecerat& other);
    Dispecerat& operator=(const Dispecerat& other);

    void adaugaVehicul(const Vehicul& v);
    [[nodiscard]] bool existaVehicul(int id) const;
    void stergeVehicul(int id);
    void afiseazaVehicule() const;
    void sorteazaVehiculeDupaCapacitate();
    void filtreazaVehiculeDupaTip(const std::string& tip) const;

    void adaugaRuta(const Ruta& ruta);
    void afiseazaRute() const;
    [[nodiscard]] bool existaRuta(const std::string& nume) const;
    void stergeRuta(const std::string& nume);
    [[nodiscard]] const Ruta* gasesteRuta(const std::string& nume) const;

    void adaugaIncident(const Incident& incident);
    void afiseazaIncidente() const;
    [[nodiscard]] int calculeazaImpactTotal() const;

    double simuleazaCursa(int idVehicul, const std::string& numeRuta);
    [[nodiscard]] double calculeazaTimpTotal(const std::string& numeRuta) const;

    void vindeBilet(bool redus, double pret, double reducere = 0.0);
    [[nodiscard]] double calculeazaVenituriTotale() const;

    void genereazaRaportActivitate() const;

    Mentenanta& getManagementTehnic();
    SistemTicketing& getSistemTicketing();

    [[nodiscard]] const std::vector<Vehicul*>& getVehicule() const;
    [[nodiscard]] const std::vector<Ruta>& getRute() const;
    [[nodiscard]] const std::vector<Incident>& getIncidente() const;

    template <typename T>
    [[nodiscard]] int numaraVehiculeDeTip() const {
        int count = 0;
        for (const auto* v : vehicule) {
            if (dynamic_cast<const T*>(v)) {
                count++;
            }
        }
        return count;
    }
};

#endif