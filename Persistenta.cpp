#include "Persistenta.hpp"

#include <fstream>
#include <sstream>

#include "Dispecerat.hpp"
#include "Autobuz.hpp"
#include "Tramvai.hpp"
#include "Metrou.hpp"
#include "Ruta.hpp"
#include "Incident.hpp"
#include "Exceptii.hpp"

// salvare

void Persistenta::salveaza(
    const Dispecerat& d,
    const std::string& numeFisier
) {
    std::ofstream fout(numeFisier);
    if (!fout) {
        throw TransportException(
            "Nu se poate deschide fisierul pentru salvare."
        );
    }

    // rute
    fout << "[RUTE]\n";
    for (const auto& r : d.getRute()) {
        fout << r.getNume() << ";"
             << r.getDistanta() << "\n";
    }

    // vehicule
    fout << "[VEHICULE]\n";
    for (const auto v : d.getVehicule()) {
        fout << v->getTip() << ";"
             << v->getId() << ";"
             << v->getCapacitate() << "\n";
    }

    // incidente
    fout << "[INCIDENTE]\n";
    for (const auto& i : d.getIncidente()) {
        fout << static_cast<int>(i.getTip()) << ";"
             << i.getImpactMinute() << ";"
             << i.getDescriere() << "\n";
    }
}

// incarcare

void Persistenta::incarca(
    Dispecerat& d,
    const std::string& numeFisier
) {
    std::ifstream fin(numeFisier);
    if (!fin) {
        throw TransportException(
            "Nu se poate deschide fisierul pentru incarcare."
        );
    }

    std::string linie;

    // sectiunile fisierului
    enum Sectiune { NIMIC, RUTE, VEHICULE, INCIDENTE };
    Sectiune sect = NIMIC;

    while (std::getline(fin, linie)) {

        // detectare sectiuni
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

        if (linie.empty()) {
            continue;
        }

        std::stringstream ss(linie);

        // rute
        if (sect == RUTE) {
            std::string nume;
            double dist;

            std::getline(ss, nume, ';');
            ss >> dist;

            d.adaugaRuta(Ruta(nume, dist));
        }

        // vehicule
        else if (sect == VEHICULE) {
            std::string tip;
            int id, cap;

            std::getline(ss, tip, ';');
            ss >> id;
            ss.ignore();
            ss >> cap;

            if (tip == "Autobuz") {
                d.adaugaVehicul(Autobuz(id, cap));
            }
            else if (tip == "Tramvai") {
                d.adaugaVehicul(Tramvai(id, cap));
            }
            else if (tip == "Metrou") {
                d.adaugaVehicul(Metrou(id, cap));
            }
        }

        // incidente
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

// validare

bool Persistenta::fisierValid(
    const std::string& numeFisier
) {
    std::ifstream fin(numeFisier);
    return fin.good();
}

// raport

void Persistenta::salveazaRaport(
    const Dispecerat& d,
    const std::string& fisier
) {
    std::ofstream fout(fisier);
    if (!fout) {
        throw TransportException(
            "Nu se poate crea fisierul de raport."
        );
    }

    fout << "=== RAPORT SISTEM TRANSPORT ===\n";
    fout << "Numar vehicule: "
         << d.numarVehicule() << "\n";
    fout << "Numar incidente: "
         << d.numarIncidente() << "\n";
    fout << "Impact total (minute): "
         << d.calculeazaImpactTotal() << "\n";
}
