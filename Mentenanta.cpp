#include "Mentenanta.hpp"
#include <iostream>
#include <ranges>

void Mentenanta::actualizeazaKilometraj(int id, int km) {
    kmParcursi[id] += km;
    if (kmParcursi[id] >= PRAG_REVIZIE && statusFlota[id] == StareVehicul::FUNCTIONAL) {
        statusFlota[id] = StareVehicul::REPARATII_NECESARE;
    }
}

void Mentenanta::trimiteInService(int id, const std::string& motiv) {
    statusFlota[id] = StareVehicul::IN_SERVICE;
    istoricService[id].push_back("Intrare Service: " + motiv);
}

void Mentenanta::reparaVehicul(int id) {
    statusFlota[id] = StareVehicul::FUNCTIONAL;
    kmParcursi[id] = 0;
    istoricService[id].emplace_back("Reparatie finalizata. Kilometraj resetat.");
}

bool Mentenanta::poateRula(int id) const {
    if (!statusFlota.contains(id)) return true;
    return statusFlota.at(id) == StareVehicul::FUNCTIONAL;
}

std::string Mentenanta::getStatusDetalii(int id) const {
    if (!statusFlota.contains(id)) return "NOU/NEINREGISTRAT";

    StareVehicul s = statusFlota.at(id);
    std::string txt;
    switch(s) {
        case StareVehicul::FUNCTIONAL: txt = "OPTIM"; break;
        case StareVehicul::REPARATII_NECESARE: txt = "REVIZIE NECESARA"; break;
        case StareVehicul::IN_SERVICE: txt = "IN REPARATIE"; break;
        case StareVehicul::CASAT: txt = "SCOS DIN UZ"; break;
        default: txt = "NECUNOSCUT"; break;
    }

    int km = kmParcursi.contains(id) ? kmParcursi.at(id) : 0;
    return txt + " (" + std::to_string(km) + " km)";
}

void Mentenanta::genereazaRaportTehnic() const {
    std::cout << "\n========== RAPORT TEHNIC FLOTA ==========\n";
    for (int id : kmParcursi | std::views::keys) {
        std::cout << "ID: " << id << " | Status: " << getStatusDetalii(id) << "\n";
        if (istoricService.contains(id)) {
            for (const auto& log : istoricService.at(id)) {
                std::cout << "  - " << log << "\n";
            }
        }
    }
    std::cout << "=========================================\n";
}

void Mentenanta::adaugaNotitaTehnica(int id, const std::string& nota) {
    istoricService[id].push_back("Nota: " + nota);
}

int Mentenanta::getKilometri(int id) const {
    if (kmParcursi.contains(id)) return kmParcursi.at(id);
    return 0;
}