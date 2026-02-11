#include "Dispecerat.hpp"
#include "Logger.hpp"
#include "Exceptii.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

Dispecerat::Dispecerat() = default;

Dispecerat::~Dispecerat() noexcept {
    elibereazaMemorie();
}

void Dispecerat::elibereazaMemorie() {
    for (auto v : vehicule) {
        delete v;
    }
    vehicule.clear();
}

Dispecerat::Dispecerat(const Dispecerat& other) {
    for (const auto v : other.vehicule) {
        vehicule.push_back(v->clone());
    }
    rute = other.rute;
    incidente = other.incidente;
}

Dispecerat& Dispecerat::operator=(const Dispecerat& other) {
    if (this != &other) {
        elibereazaMemorie();

        for (const auto v : other.vehicule) {
            this->vehicule.push_back(v->clone());
        }

        this->rute = other.rute;
        this->incidente = other.incidente;

        this->managementTehnic = other.managementTehnic;
        this->sistemTicketing = other.sistemTicketing;
    }
    Logger::getInstance().log(LogLevel::INFO, "Dispecerat copiat prin operatorul de atribuire.");
    return *this;
}

void Dispecerat::adaugaVehicul(const Vehicul& v) {
    if (existaVehicul(v.getId())) {
        throw VehiculException("ID vehicul duplicat!");
    }
    vehicule.push_back(v.clone());
    Logger::getInstance().log(LogLevel::INFO, "Vehicul ID " + std::to_string(v.getId()) + " adaugat.");
}

bool Dispecerat::existaVehicul(int id) const {
    return std::ranges::any_of(vehicule, [id](const Vehicul* v) {
        return v->getId() == id;
    });
}

void Dispecerat::stergeVehicul(int id) {
    auto it = std::ranges::find_if(vehicule, [id](const Vehicul* v) {
        return v->getId() == id;
    });

    if (it != vehicule.end()) {
        delete *it;
        vehicule.erase(it);
        Logger::getInstance().log(LogLevel::INFO, "Vehicul ID " + std::to_string(id) + " sters.");
    } else {
        throw VehiculException("Vehiculul nu a fost gasit pentru stergere.");
    }
}

void Dispecerat::afiseazaVehicule() const {
    if (vehicule.empty()) {
        std::cout << "Flota este goala.\n";
        return;
    }
    std::ranges::for_each(vehicule, [this](const Vehicul* v) {
        std::cout << v->getTip() << " | ID: " << v->getId()
                  << " | Status: " << managementTehnic.getStatusDetalii(v->getId()) << "\n";
    });
}

void Dispecerat::sorteazaVehiculeDupaCapacitate() {
    std::ranges::sort(vehicule, [](const Vehicul* a, const Vehicul* b) {
        return a->getCapacitate() > b->getCapacitate();
    });
}

void Dispecerat::filtreazaVehiculeDupaTip(const std::string& tip) const {
    std::cout << "--- Filtrare tip: " << tip << " ---\n";
    for (const auto v : vehicule) {
        if (v->getTip() == tip) std::cout << v->descriere() << "\n";
    }
}

void Dispecerat::adaugaRuta(const Ruta& ruta) {
    if (existaRuta(ruta.getNume())) {
        throw RutaException("Ruta deja existenta.");
    }
    rute.push_back(ruta);
}

void Dispecerat::afiseazaRute() const {
    if (rute.empty()) {
        std::cout << "Nu sunt rute configurate.\n";
        return;
    }
    std::ranges::for_each(rute, [](const Ruta& r) {
        std::cout << "Ruta: " << r.getNume() << " | Distanta: " << r.getDistanta() << " km\n";
    });
}

bool Dispecerat::existaRuta(const std::string& nume) const {
    return std::ranges::any_of(rute, [&nume](const Ruta& r) {
        return r.getNume() == nume;
    });
}

void Dispecerat::stergeRuta(const std::string& nume) {
    auto it = std::ranges::find_if(rute, [&nume](const Ruta& r) {
        return r.getNume() == nume;
    });

    if (it != rute.end()) {
        rute.erase(it);
    } else {
        throw RutaException("Ruta nu exista.");
    }
}

const Ruta* Dispecerat::gasesteRuta(const std::string& nume) const {
    auto it = std::ranges::find_if(rute, [&nume](const Ruta& r) {
        return r.getNume() == nume;
    });
    return (it != rute.end()) ? &(*it) : nullptr;
}

void Dispecerat::adaugaIncident(const Incident& incident) {
    incidente.push_back(incident);
    Logger::getInstance().log(LogLevel::WARNING, "Incident nou: " + incident.getDescriere());
}

void Dispecerat::afiseazaIncidente() const {
    if (incidente.empty()) {
        std::cout << "Nu sunt incidente raportate.\n";
        return;
    }
    for (const auto& i : incidente) {
        std::cout << "Alerta: " << i.getDescriere() << " | +" << i.getImpactMinute() << " min\n";
    }
}

int Dispecerat::calculeazaImpactTotal() const {
    return std::accumulate(incidente.begin(), incidente.end(), 0,
        [](int acc, const Incident& i) { return acc + i.getImpactMinute(); });
}

double Dispecerat::simuleazaCursa(int idVehicul, const std::string& numeRuta) {
    if (!managementTehnic.poateRula(idVehicul)) {
        throw TransportException("Vehiculul este in service!");
    }

    const Ruta* ruta = gasesteRuta(numeRuta);
    if (!ruta) throw RutaException("Ruta nu a fost gasita.");

    auto it = std::ranges::find_if(vehicule, [idVehicul](const Vehicul* v) {
        return v->getId() == idVehicul;
    });

    if (it == vehicule.end()) throw VehiculException("Vehicul inexistent.");

    double timp = (*it)->calculeazaTimp(*ruta);
    timp += (calculeazaImpactTotal() / 60.0);

    managementTehnic.actualizeazaKilometraj(idVehicul, static_cast<int>(ruta->getDistanta()));
    return timp;
}

double Dispecerat::calculeazaTimpTotal(const std::string& numeRuta) const {
    const Ruta* ruta = gasesteRuta(numeRuta);
    if (!ruta) throw RutaException("Ruta nu exista.");

    double timpMinim = 999999.0;
    for (const auto v : vehicule) {
        double t = v->calculeazaTimp(*ruta);
        if (t < timpMinim) timpMinim = t;
    }
    return timpMinim + (calculeazaImpactTotal() / 60.0);
}

void Dispecerat::vindeBilet(bool redus, double pret, double reducere) {
    if (redus) sistemTicketing.emiteBiletRedus(pret, reducere);
    else sistemTicketing.emiteBiletIntreg(pret);
}

double Dispecerat::calculeazaVenituriTotale() const {
    return sistemTicketing.calculeazaVenituri();
}

void Dispecerat::genereazaRaportActivitate() const {
    std::cout << "\n========== RAPORT ACTIVITATE ==========\n";
    std::cout << "Vehicule: " << vehicule.size() << "\n";
    std::cout << "Rute: " << rute.size() << "\n";
    std::cout << "Venituri: " << calculeazaVenituriTotale() << " RON\n";
    std::cout << "=======================================\n";
}

Mentenanta& Dispecerat::getManagementTehnic() { return managementTehnic; }
SistemTicketing& Dispecerat::getSistemTicketing() { return sistemTicketing; }
const std::vector<Vehicul*>& Dispecerat::getVehicule() const { return vehicule; }
const std::vector<Ruta>& Dispecerat::getRute() const { return rute; }
const std::vector<Incident>& Dispecerat::getIncidente() const { return incidente; }