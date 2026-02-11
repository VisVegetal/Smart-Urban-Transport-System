#ifndef DISPECERAT_HPP
#define DISPECERAT_HPP

#include <vector>
#include <string>

#include "Vehicul.hpp"
#include "Ruta.hpp"
#include "Incident.hpp"

class Dispecerat {
private:
    std::vector<Vehicul*> vehicule; // vehicule gestionate
    std::vector<Ruta> rute; // rutele disponibile
    std::vector<Incident> incidente; // incidente active

    void elibereazaMemorie();

public:
    Dispecerat();
    ~Dispecerat() noexcept;

    Dispecerat(const Dispecerat& other);

    Dispecerat& operator=(Dispecerat other);

    [[nodiscard]] const std::vector<Vehicul*>& getVehicule() const;
    [[nodiscard]] const std::vector<Ruta>& getRute() const;
    [[nodiscard]] const std::vector<Incident>& getIncidente() const;

    // operatii pe rute
    [[nodiscard]] bool existaRuta(const std::string& nume) const;
    void stergeRuta(const std::string& nume);

    // statistici simple
    [[nodiscard]] int numarVehicule() const;
    [[nodiscard]] int numarIncidente() const;

    // operatii pe vehicule
    void adaugaVehicul(const Vehicul& v);
    [[nodiscard]] bool existaVehicul(int id) const;
    void stergeVehicul(int id);
    void afiseazaVehicule() const;

    // operatii pe rute
    void adaugaRuta(const Ruta& ruta);
    void afiseazaRute() const;
    [[nodiscard]] const Ruta* gasesteRuta(const std::string& nume) const;

    // operatii pe incidente
    void adaugaIncident(const Incident& incident);
    void afiseazaIncidente() const;
    [[nodiscard]] int calculeazaImpactTotal() const;

    // simuleaza o cursa pentru un vehicul pe o ruta
    [[nodiscard]] double simuleazaCursa(
        int idVehicul,
        const std::string& numeRuta
    ) const;

    // timpul total pe o ruta
    [[nodiscard]] double calculeazaTimpTotal(const std::string& numeRuta) const;

    [[nodiscard]] double calculeazaVenituriTotale() const;
};

#endif
