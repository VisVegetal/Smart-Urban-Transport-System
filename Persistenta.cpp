#include "Persistenta.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include "Autobuz.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Exceptii.hpp"

// ================= SALVARE =================

void Persistenta::salveaza(
    const Dispecerat& d,
    const std::string& numeFisier
) {
    std::ofstream fout(numeFisier);
    if (!fout) {
        throw TransportException("Nu se poate deschide fisierul pentru salvare.");
    }

    // -------- RUTE --------
    fout << "[RUTE]\n";
    for (const auto& r : d.getRute()) {
        fout << r.getNume() << ";" << r.getDistanta() << "\n";
    }

    // -------- VEHICULE --------
    fout << "[VEHICULE]\n";
    for (const auto v : d.getVehicule()) {
        fout << v->getTip() << ";"
             << v->getId() << ";"
             << v->getCapacitate() << "\n";
    }

    // -------- INCIDENTE --------
    fout << "[INCIDENTE]\n";
    for (const auto& i : d.getIncidente()) {
        fout << static_cast<int>(i.getTip()) << ";"
             << i.getImpactMinute() << ";"
             << i.getDescriere() << "\n";
    }
}

// ================= INCARCARE =================

void Persistenta::incarca(
    Dispecerat& d,
    const std::string& numeFisier
) {
    std::ifstream fin(numeFisier);
    if (!fin) {
        throw TransportException("Nu se poate deschide fisierul pentru incarcare.");
    }

    std::string linie;
    enum Sectiune { NIMIC, RUTE, VEHICULE, INCIDENTE };
    Sectiune sect = NIMIC;

    while (std::getline(fin, linie)) {
        if (linie == "[RUTE]") {
            sect = RUTE;
            continue;
        }
        if (linie == "[VEHICULE]") {
            sect = VEHICULE;
            continue;
        }
        if (linie == "[INCIDENTE]") {
            sect = INCIDENTE;
            continue;
        }

        if (linie.empty()) continue;

        std::stringstream ss(linie);

        if (sect == RUTE) {
            std::string nume;
            double dist;
            std::getline(ss, nume, ';');
            ss >> dist;

            d.adaugaRuta(Ruta(nume, dist));
        }
        else if (sect == VEHICULE) {
            std::string tip;
            int id, cap;

            std::getline(ss, tip, ';');
            ss >> id;
            ss.ignore();
            ss >> cap;

            if (tip == "Autobuz") {
                d.adaugaVehicul(Autobuz(id, cap));
            } else if (tip == "Tramvai") {
                d.adaugaVehicul(Tramvai(id, cap));
            } else if (tip == "Metrou") {
                d.adaugaVehicul(Metrou(id, cap));
            }
        }
        else if (sect == INCIDENTE) {
            int tipInt, impact;
            std::string descriere;

            ss >> tipInt;
            ss.ignore();
            ss >> impact;
            ss.ignore();
            std::getline(ss, descriere);

            d.adaugaIncident(
                Incident(
                    static_cast<TipIncident>(tipInt),
                    descriere,
                    impact
                )
            );
        }
    }
}
