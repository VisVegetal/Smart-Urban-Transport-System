#include "Persistenta.hpp"
#include "VehiculFactory.hpp"
#include "Exceptii.hpp"
#include <fstream>
#include <sstream>

void Persistenta::salveazaSistem(const Dispecerat& d, const std::string& numeFisier) {
    std::ofstream f(numeFisier);
    if (!f.is_open()) throw TransportException("Nu s-a putut deschide fisierul pentru salvare.");

    f << "VEHICULE_START\n";
    for (const auto v : d.getVehicule()) {
        int tipInt = (v->getTip() == "Autobuz") ? 1 : (v->getTip() == "Tramvai") ? 2 : 3;
        f << tipInt << " " << v->getId() << " " << v->getCapacitate() << "\n";
    }
    f << "VEHICULE_END\n";

    f << "RUTE_START\n";
    for (const auto& r : d.getRute()) {
        f << r.getNume() << ";" << r.getDistanta() << "\n";
    }
    f << "RUTE_END\n";

    f.close();
}

void Persistenta::incarcaSistem(Dispecerat& d, const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) throw TransportException("Fisierul de date nu exista.");

    std::string linie;
    std::string sectiuneCurenta;

    while (std::getline(f, linie)) {
        if (linie == "VEHICULE_START") { sectiuneCurenta = "VEHICULE"; continue; }
        if (linie == "RUTE_START") { sectiuneCurenta = "RUTE"; continue; }
        if (linie.find("_END") != std::string::npos) { sectiuneCurenta = ""; continue; }

        if (sectiuneCurenta == "VEHICULE") {
            std::stringstream ss(linie);
            int tip, id, cap;
            if (ss >> tip >> id >> cap) {
                auto v = VehiculFactory::creeazaVehicul(tip, id, cap);
                if (!d.existaVehicul(id)) d.adaugaVehicul(*v);
            }
        }
        else if (sectiuneCurenta == "RUTE") {
            size_t delim = linie.find(';');
            if (delim != std::string::npos) {
                std::string nume = linie.substr(0, delim);
                double dist = std::stod(linie.substr(delim + 1));
                if (!d.existaRuta(nume)) d.adaugaRuta(Ruta(nume, dist));
            }
        }
    }
    f.close();
}

bool Persistenta::esteFisierValid(const std::string& numeFisier) {
    std::ifstream f(numeFisier);
    if (!f.is_open()) return false;

    std::string primaLinie;
    std::getline(f, primaLinie);
    f.close();

    return (primaLinie == "VEHICULE_START");
}

void Persistenta::creeazaBackup(const std::string& sursa, const std::string& destinatie) {
    std::ifstream src(sursa, std::ios::binary);
    std::ofstream dst(destinatie, std::ios::binary);

    if (src.is_open() && dst.is_open()) {
        dst << src.rdbuf();
    }
    src.close();
    dst.close();
}