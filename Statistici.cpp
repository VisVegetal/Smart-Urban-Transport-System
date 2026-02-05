#include "Statistici.hpp"

#include <iostream>
#include <limits>

// ================= VEHICUL CEL MAI RAPID =================

const Vehicul* Statistici::vehiculCelMaiRapid(
    const Dispecerat& d,
    const std::string& numeRuta
) {
    const Ruta* ruta = d.gasesteRuta(numeRuta);
    if (!ruta) {
        throw RutaException("Ruta inexistenta pentru statistici.");
    }

    const Vehicul* vehiculRapid = nullptr;
    double timpMinim = std::numeric_limits<double>::max();

    for (const auto v : d.getVehicule()) {
        double timp = v->calculeazaTimp(*ruta);
        if (timp < timpMinim) {
            timpMinim = timp;
            vehiculRapid = v;
        }
    }

    return vehiculRapid;
}

// ================= VEHICUL CU CAPACITATE MAXIMA =================

const Vehicul* Statistici::vehiculCapacitateMaxima(
    const Dispecerat& d
) {
    const Vehicul* vehiculMax = nullptr;
    int capacitateMax = -1;

    for (const auto v : d.getVehicule()) {
        if (v->getCapacitate() > capacitateMax) {
            capacitateMax = v->getCapacitate();
            vehiculMax = v;
        }
    }

    return vehiculMax;
}


double Statistici::timpMediuPeRuta(
    const Dispecerat& d,
    const std::string& numeRuta
) {
    const Ruta* ruta = d.gasesteRuta(numeRuta);
    if (!ruta) {
        throw RutaException("Ruta inexistenta pentru calculul timpului mediu.");
    }

    double sumaTimp = 0.0;
    int numarVehicule = 0;

    for (const auto v : d.getVehicule()) {
        sumaTimp += v->calculeazaTimp(*ruta);
        ++numarVehicule;
    }

    if (numarVehicule == 0) {
        return 0.0;
    }

    return sumaTimp / numarVehicule;
}

// ================= RAPORT GENERAL =================

void Statistici::raportGeneral(
    const Dispecerat& d
) {
    std::cout << "\n===== RAPORT GENERAL SISTEM =====\n";
    std::cout << "Numar total vehicule: "
              << d.getVehicule().size() << "\n";

    std::cout << "Raport generat cu succes.\n";
}
