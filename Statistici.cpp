#include "Statistici.hpp"

#include "Autobuz.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Exceptii.hpp"
#include "Statie.hpp"

#include <iostream>
#include <limits>


//  vehiculul cu timpul minim de parcurgere pe o ruta
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


//  vehiculul cu cea mai mare capacitate
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


//  timpul mediu de parcurgere al unei rute
double Statistici::timpMediuPeRuta(
    const Dispecerat& d,
    const std::string& numeRuta
) {
    const Ruta* ruta = d.gasesteRuta(numeRuta);
    if (!ruta) {
        throw RutaException(
            "Ruta inexistenta pentru calculul timpului mediu."
        );
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

// raport sumar al sistemului
void Statistici::raportGeneral(const Dispecerat& d) {
    std::cout << "\n===== RAPORT GENERAL SISTEM =====\n";

    std::cout << "Numar vehicule: " << d.numarVehicule() << "\n";
    std::cout << "Numar incidente: " << d.numarIncidente() << "\n";

    // Exemplu de statii simbolice
    Statie s1("Centru");
    Statie s2("Aeroport");

    for (const auto& r : d.getRute()) {
        s1.adaugaRuta(r.getNume());
        s2.adaugaRuta(r.getNume());
    }

    s1.afiseaza();
    s2.afiseaza();

    std::cout << "================================\n";
}



//  distributia vehiculelor pe tipuri folosind dynamic_cast
void Statistici::distributieVehicule(const Dispecerat& d) {
    int autobuze = 0;
    int tramvaie = 0;
    int metrouri = 0;

    std::cout << "\n===== DISTRIBUTIE VEHICULE PE TIP =====\n";

    for (const auto v : d.getVehicule()) {

        if (const auto* a = dynamic_cast<const Autobuz*>(v)) {
            ++autobuze;
            std::cout << "[Autobuz] ID " << a->getId()
                      << " | Capacitate: " << a->getCapacitate()
                      << " | Banda dedicata: "
                      << (a->areBandaDedicata() ? "DA" : "NU") << "\n";
        }
        else if (const auto* t = dynamic_cast<const Tramvai*>(v)) {
            ++tramvaie;
            std::cout << "[Tramvai] ID " << t->getId()
                      << " | Capacitate: " << t->getCapacitate()
                      << " | Prioritate intersectii: "
                      << (t->arePrioritate() ? "DA" : "NU") << "\n";
        }
        else if (const auto* m = dynamic_cast<const Metrou*>(v)) {
            ++metrouri;
            std::cout << "[Metrou] ID " << m->getId()
                      << " | Capacitate: " << m->getCapacitate()
                      << " | Interval: " << m->getIntervalMinute()
                      << " min | Sistem automat: "
                      << (m->esteAutomat() ? "DA" : "NU") << "\n";
        }
    }

    std::cout << "\n----- SUMAR -----\n";
    std::cout << "Autobuze: " << autobuze << "\n";
    std::cout << "Tramvaie: " << tramvaie << "\n";
    std::cout << "Metrouri: " << metrouri << "\n";
    std::cout << "===============================\n";
}


// impactul mediu al incidentelor active
double Statistici::impactMediuIncident(
    const Dispecerat& d
) {
    if (d.getIncidente().empty()) {
        return 0.0;
    }

    int total = 0;
    for (const auto& i : d.getIncidente()) {
        total += i.getImpactMinute();
    }

    return static_cast<double>(total)
           / static_cast<double>(d.getIncidente().size());
}

//  raport detaliat al starii sistemului
void Statistici::raportDetaliat(const Dispecerat& d) {
    std::cout << "\n===== RAPORT DETALIAT SISTEM =====\n";

    for (const auto v : d.getVehicule()) {

        if (const auto* a = dynamic_cast<const Autobuz*>(v)) {
            std::cout << "[Autobuz] ID " << a->getId()
                      << " | Capacitate: " << a->getCapacitate()
                      << " | Opriri: " << a->getNumarOpriri()
                      << " | Semafoare: " << a->getNumarSemafoare()
                      << " | Banda dedicata: "
                      << (a->areBandaDedicata() ? "DA" : "NU") << "\n";
        }
        else if (const auto* t = dynamic_cast<const Tramvai*>(v)) {
            std::cout << "[Tramvai] ID " << t->getId()
                      << " | Capacitate: " << t->getCapacitate()
                      << " | Semafoare: " << t->getNumarSemafoare()
                      << " | Prioritate: "
                      << (t->arePrioritate() ? "DA" : "NU") << "\n";
        }
        else if (const auto* m = dynamic_cast<const Metrou*>(v)) {
            std::cout << "[Metrou] ID " << m->getId()
                      << " | Capacitate: " << m->getCapacitate()
                      << " | Interval: " << m->getIntervalMinute()
                      << " min | Automat: "
                      << (m->esteAutomat() ? "DA" : "NU") << "\n";
        }
    }

    std::cout << "Impact mediu per incident: "
          << impactMediuIncident(d)
          << " minute\n";


    std::cout << "=================================\n";
}