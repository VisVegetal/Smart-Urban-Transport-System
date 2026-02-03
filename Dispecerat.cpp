#include "Dispecerat.hpp"
#include "Metrou.hpp"
#include <iostream>
#include <algorithm>



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
        throw VehiculException("Exista deja un vehicul cu acest ID.");
    }
    vehicule.push_back(v.clone());
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

    for (const auto v : vehicule) {
        timpTotal += v->calculeazaTimp(*ruta);

        if (dynamic_cast<const Metrou*>(v)) {
            timpTotal *= 0.97;
        }
    }

    timpTotal += calculeazaImpactTotal() / 60.0;

    return timpTotal;
}
