#include "Statistici.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Autobuz.hpp"
#include "Dispecerat.hpp"


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

void Statistici::distributieVehicule(const Dispecerat& d) {
    int autobuze = 0, tramvaie = 0, metrouri = 0;

    for (const auto v : d.getVehicule()) {
        if (dynamic_cast<const Autobuz*>(v)) autobuze++;
        else if (dynamic_cast<const Tramvai*>(v)) tramvaie++;
        else if (dynamic_cast<const Metrou*>(v)) metrouri++;
    }

    std::cout << "Autobuze: " << autobuze << "\n";
    std::cout << "Tramvaie: " << tramvaie << "\n";
    std::cout << "Metrouri: " << metrouri << "\n";
}

double Statistici::impactMediuIncident(const Dispecerat& d) {
    if (d.getIncidente().empty()) return 0.0;

    int total = 0;
    for (const auto& i : d.getIncidente()) {
        total += i.getImpactMinute();
    }

    return static_cast<double>(total) / d.getIncidente().size();
}

void Statistici::raportDetaliat(const Dispecerat& d) {
    std::cout << "\n===== RAPORT DETALIAT SISTEM =====\n";
    std::cout << "Vehicule totale: " << d.numarVehicule() << "\n";
    std::cout << "Incidente active: " << d.numarIncidente() << "\n";
    std::cout << "Impact mediu incident: "
              << impactMediuIncident(d) << " minute\n";
}
