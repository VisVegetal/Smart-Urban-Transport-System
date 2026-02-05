#include "Dispecerat.hpp"
#include "Metrou.hpp"
#include "Logger.hpp"
#include <iostream>


void Dispecerat::elibereazaMemorie() {
    for (auto v : vehicule) {
        delete v;
    }
    vehicule.clear();
}


Dispecerat::Dispecerat() = default;

Dispecerat::~Dispecerat() {
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

void Dispecerat::adaugaVehicul(const Vehicul& v) {
    if (existaVehicul(v.getId())) {
        Logger::log(LogLevel::ERROR, "ID vehicul duplicat");
        throw VehiculException("Exista deja un vehicul cu acest ID.");
    }
    vehicule.push_back(v.clone());
    Logger::log(LogLevel::INFO, "Vehicul adaugat: ID " + std::to_string(v.getId()));
}



bool Dispecerat::existaVehicul(int id) const {
    for (const auto v : vehicule) {
        if (v->getId() == id) {
            return true;
        }
    }
    return false;
}

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


void Dispecerat::adaugaRuta(const Ruta& ruta) {
    rute.push_back(ruta);
}

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

const Ruta* Dispecerat::gasesteRuta(const std::string& nume) const {
    for (const auto& r : rute) {
        if (r.getNume() == nume) {
            return &r;
        }
    }
    return nullptr;
}

void Dispecerat::adaugaIncident(const Incident& incident) {
    incidente.push_back(incident);
    Logger::log(LogLevel::WARNING, "Incident adaugat: " + incident.getDescriere());
}



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

int Dispecerat::calculeazaImpactTotal() const {
    int total = 0;
    for (const auto& i : incidente) {
        total += i.getImpactMinute();
    }
    return total;
}


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

    if (existaMetrou) {
        timpTotal *= 0.97;
    }


    timpTotal += calculeazaImpactTotal() / 60.0;

    return timpTotal;
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

bool Dispecerat::existaRuta(const std::string& nume) const {
    for (const auto& r : rute) {
        if (r.getNume() == nume) return true;
    }
    return false;
}

int Dispecerat::numarVehicule() const {
    return static_cast<int>(vehicule.size());
}

int Dispecerat::numarIncidente() const {
    return static_cast<int>(incidente.size());
}

void Dispecerat::stergeRuta(const std::string& nume) {
    for (auto it = rute.begin(); it != rute.end(); ++it) {
        if (it->getNume() == nume) {
            rute.erase(it);
            Logger::log(LogLevel::INFO, "Ruta stearsa: " + nume);
            return;
        }
    }

    throw RutaException("Ruta inexistenta.");
}

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

