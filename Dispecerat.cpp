#include "Dispecerat.hpp"
#include "Metrou.hpp"
#include "Logger.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

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

void Dispecerat::adaugaVehicul(const Vehicul& v) {
    if (existaVehicul(v.getId())) {
        Logger::getInstance().log(LogLevel::ERROR, "ID vehicul duplicat");
        throw VehiculException("Exista deja un vehicul cu acest ID.");
    }
    vehicule.push_back(v.clone());
    Logger::getInstance().log(LogLevel::INFO, "Vehicul adaugat: ID " + std::to_string(v.getId()));
}

bool Dispecerat::existaVehicul(int id) const {
    for (const auto v : vehicule) {
        if (v->getId() == id) return true;
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
        std::cout << v->getTip() << " | ID: " << v->getId()
                  << " | Status: " << managementTehnic.getStatusDetalii(v->getId()) << "\n";
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
        std::cout << "Ruta: " << r.getNume() << " | Distanta: " << r.getDistanta() << " km\n";
    }
}

const Ruta* Dispecerat::gasesteRuta(const std::string& nume) const {
    for (const auto& r : rute) {
        if (r.getNume() == nume) return &r;
    }
    return nullptr;
}

void Dispecerat::adaugaIncident(const Incident& incident) {
    incidente.push_back(incident);
    Logger::getInstance().log(LogLevel::WARNING, "Incident adaugat: " + incident.getDescriere());
}

int Dispecerat::calculeazaImpactTotal() const {
    int total = 0;
    for (const auto& i : incidente) total += i.getImpactMinute();
    return total;
}

double Dispecerat::calculeazaTimpTotal(const std::string& numeRuta) const {
    const Ruta* ruta = gasesteRuta(numeRuta);
    if (!ruta) throw RutaException("Ruta nu exista.");
    double timpTotal = 0.0;
    for (const auto v : vehicule) {
        timpTotal += v->calculeazaTimp(*ruta);
    }
    timpTotal += calculeazaImpactTotal() / 60.0;
    return timpTotal;
}

double Dispecerat::simuleazaCursa(int idVehicul, const std::string& numeRuta) {
    if (!managementTehnic.poateRula(idVehicul)) {
        throw TransportException("Vehiculul nu poate rula. Verificati starea tehnica!");
    }

    const Ruta* ruta = gasesteRuta(numeRuta);
    if (!ruta) throw RutaException("Ruta inexistenta.");

    for (const auto v : vehicule) {
        if (v->getId() == idVehicul) {
            double timp = v->calculeazaTimp(*ruta);
            timp += calculeazaImpactTotal() / 60.0;
            managementTehnic.actualizeazaKilometraj(idVehicul, static_cast<int>(ruta->getDistanta()));
            return timp;
        }
    }
    throw VehiculException("Vehicul inexistent.");
}

double Dispecerat::calculeazaVenituriTotale() const {
    return sistemTicketing.calculeazaVenituri();
}

void Dispecerat::vindeBilet(bool redus, double pret, double reducere) {
    if (redus) sistemTicketing.emiteBiletRedus(pret, reducere);
    else sistemTicketing.emiteBiletIntreg(pret);
}

void Dispecerat::sorteazaVehiculeDupaCapacitate() {
    std::sort(vehicule.begin(), vehicule.end(), [](Vehicul* a, Vehicul* b) {
        return a->getCapacitate() > b->getCapacitate();
    });
}

void Dispecerat::filtreazaVehiculeDupaTip(const std::string& tip) const {
    std::cout << "--- Filtrare: " << tip << " ---\n";
    for (const auto v : vehicule) {
        if (v->getTip() == tip) std::cout << v->descriere() << "\n";
    }
}

Mentenanta& Dispecerat::getMentenanta() { return managementTehnic; }
SistemTicketing& Dispecerat::getTicketing() { return sistemTicketing; }

int Dispecerat::numarVehicule() const { return static_cast<int>(vehicule.size()); }
int Dispecerat::numarIncidente() const { return static_cast<int>(incidente.size()); }
const std::vector<Vehicul*>& Dispecerat::getVehicule() const { return vehicule; }
const std::vector<Ruta>& Dispecerat::getRute() const { return rute; }
const std::vector<Incident>& Dispecerat::getIncidente() const { return incidente; }

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

bool Dispecerat::existaRuta(const std::string& nume) const {
    for (const auto& r : rute) {
        if (r.getNume() == nume) return true;
    }
    return false;
}

void Dispecerat::stergeRuta(const std::string& nume) {
    for (auto it = rute.begin(); it != rute.end(); ++it) {
        if (it->getNume() == nume) {
            rute.erase(it);
            Logger::getInstance().log(LogLevel::INFO, "Ruta stearsa: " + nume);
            return;
        }
    }
    throw RutaException("Ruta nu a putut fi stearsa deoarece nu exista.");
}

Mentenanta& Dispecerat::getManagementTehnic() {
    return managementTehnic;
}

SistemTicketing& Dispecerat::getSistemTicketing() {
    return sistemTicketing;
}