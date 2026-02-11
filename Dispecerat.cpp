#include "Dispecerat.hpp"
#include "Metrou.hpp"
#include "Logger.hpp"
#include <iostream>

// elibereaza memoria pentru vehiculele alocate dinamic
void Dispecerat::elibereazaMemorie() {
    for (auto v : vehicule) {
        delete v;
    }
    vehicule.clear();
}

Dispecerat::Dispecerat() = default;

Dispecerat::~Dispecerat() noexcept {
    elibereazaMemorie();
}

Dispecerat::Dispecerat(const Dispecerat& other) {
    for (const auto v : other.vehicule) {
        vehicule.push_back(v->clone());
    }
    rute = other.rute;
    incidente = other.incidente;
}

Dispecerat& Dispecerat::operator=(Dispecerat other) {
    std::swap(vehicule, other.vehicule);
    std::swap(rute, other.rute);
    std::swap(incidente, other.incidente);
    return *this;
}

// adauga un vehicul in sistem (cu verificare ID unic)
void Dispecerat::adaugaVehicul(const Vehicul& v) {
    if (existaVehicul(v.getId())) {
        Logger::getInstance().log(LogLevel::ERROR, "ID vehicul duplicat");
        throw VehiculException("Exista deja un vehicul cu acest ID.");
    }
    vehicule.push_back(v.clone());
    Logger::getInstance().log(LogLevel::INFO,
        "Vehicul adaugat: ID " + std::to_string(v.getId()));
}

// verifica existenta unui vehicul dupa ID
bool Dispecerat::existaVehicul(int id) const {
    for (const auto v : vehicule) {
        if (v->getId() == id) {
            return true;
        }
    }
    return false;
}

// sterge un vehicul dupa ID
void Dispecerat::stergeVehicul(int id) {
    for (auto it = vehicule.begin(); it != vehicule.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            vehicule.erase(it);
            return;
        }
    }
    throw VehiculException("Vehiculul cu ID-ul dat nu exista.");
}

// afiseaza toate vehiculele
void Dispecerat::afiseazaVehicule() const {
    if (vehicule.empty()) {
        std::cout << "Nu exista vehicule.\n";
        return;
    }

    for (const auto v : vehicule) {
        std::cout << v->getTip()
                  << " | ID: " << v->getId()
                  << " | Capacitate: " << v->getCapacitate()
                  << "\n";
    }
}

// adauga o ruta
void Dispecerat::adaugaRuta(const Ruta& ruta) {
    rute.push_back(ruta);
}

// afiseaza rutele disponibile
void Dispecerat::afiseazaRute() const {
    if (rute.empty()) {
        std::cout << "Nu exista rute.\n";
        return;
    }

    for (const auto& r : rute) {
        std::cout << "Ruta: " << r.getNume()
                  << " | Distanta: " << r.getDistanta()
                  << " km\n";
    }
}

// cauta o ruta dupa nume
const Ruta* Dispecerat::gasesteRuta(const std::string& nume) const {
    for (const auto& r : rute) {
        if (r.getNume() == nume) {
            return &r;
        }
    }
    return nullptr;
}

// verifica existenta unei rute
bool Dispecerat::existaRuta(const std::string& nume) const {
    for (const auto& r : rute) {
        if (r.getNume() == nume) {
            return true;
        }
    }
    return false;
}

// sterge o ruta dupa nume
void Dispecerat::stergeRuta(const std::string& nume) {
    for (auto it = rute.begin(); it != rute.end(); ++it) {
        if (it->getNume() == nume) {
            rute.erase(it);
            Logger::getInstance().log(LogLevel::INFO, "Ruta stearsa: " + nume);
            return;
        }
    }
    throw RutaException("Ruta inexistenta.");
}

// adauga un incident
void Dispecerat::adaugaIncident(const Incident& incident) {
    incidente.push_back(incident);
    Logger::getInstance().log(LogLevel::WARNING,
        "Incident adaugat: " + incident.getDescriere());
}

// afiseaza incidentele active
void Dispecerat::afiseazaIncidente() const {
    if (incidente.empty()) {
        std::cout << "Nu exista incidente active.\n";
        return;
    }

    for (const auto& i : incidente) {
        std::cout << "Incident: " << i.getDescriere()
                  << " | Impact: " << i.getImpactMinute()
                  << " minute\n";
    }
}

// calculeaza impactul total al incidentelor
int Dispecerat::calculeazaImpactTotal() const {
    int total = 0;
    for (const auto& i : incidente) {
        total += i.getImpactMinute();
    }
    return total;
}

// timpul total pe o ruta pentru toate vehiculele
double Dispecerat::calculeazaTimpTotal(const std::string& numeRuta) const {
    const Ruta* ruta = gasesteRuta(numeRuta);
    if (!ruta) {
        throw RutaException("Ruta nu exista.");
    }

    double timpTotal = 0.0;
    bool existaMetrou = false;

    for (const auto v : vehicule) {
        timpTotal += v->calculeazaTimp(*ruta);
        if (dynamic_cast<const Metrou*>(v)) {
            existaMetrou = true;
        }
    }

    // metroul imbunatateste fluxul general
    if (existaMetrou) {
        timpTotal *= 0.97;
    }

    // impactul incidentelor
    timpTotal += calculeazaImpactTotal() / 60.0;

    return timpTotal;
}

// simuleaza o cursa pentru un vehicul specific
double Dispecerat::simuleazaCursa(
    int idVehicul,
    const std::string& numeRuta
) const {
    const Ruta* ruta = gasesteRuta(numeRuta);
    if (!ruta) {
        throw RutaException("Ruta inexistenta.");
    }

    for (const auto v : vehicule) {
        if (v->getId() == idVehicul) {
            double timp = v->calculeazaTimp(*ruta);
            timp += calculeazaImpactTotal() / 60.0;
            return timp;
        }
    }

    throw VehiculException("Vehicul inexistent.");
}

// statistici simple
int Dispecerat::numarVehicule() const {
    return static_cast<int>(vehicule.size());
}

int Dispecerat::numarIncidente() const {
    return static_cast<int>(incidente.size());
}

const std::vector<Vehicul*>& Dispecerat::getVehicule() const {
    return vehicule;
}

const std::vector<Ruta>& Dispecerat::getRute() const {
    return rute;
}

const std::vector<Incident>& Dispecerat::getIncidente() const {
    return incidente;
}

double Dispecerat::calculeazaVenituriTotale() const {
    double total = 0.0;
    for (const auto v : vehicule) {
        total += v->calculeazaVenitEstimativ();
    }
    return total;
}


