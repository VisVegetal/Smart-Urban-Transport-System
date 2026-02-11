#include "Incident.hpp"
#include <utility>
#include "Exceptii.hpp"

Incident::Incident() 
    : tip(TipIncident::TRAFIC_INTENS), descriere("Necunoscut"), impactMinute(0), dataRaportarii("N/A") {}

Incident::Incident(TipIncident tip, std::string descriere, int impactMinute, std::string data)
    : tip(tip), descriere(std::move(std::move(descriere))), impactMinute(impactMinute), dataRaportarii(std::move(data)) {
    if (impactMinute < 0) throw ValoareInvalidaException("Impactul nu poate fi negativ.");
}

Incident::Incident(const Incident& other) {
    this->tip = other.tip;
    this->descriere = other.descriere;
    this->impactMinute = other.impactMinute;
    this->dataRaportarii = other.dataRaportarii;
}

Incident& Incident::operator=(const Incident& other) {
    if (this != &other) {
        this->tip = other.tip;
        this->descriere = other.descriere;
        this->impactMinute = other.impactMinute;
        this->dataRaportarii = other.dataRaportarii;
    }
    return *this;
}

TipIncident Incident::getTip() const { return tip; }
const std::string& Incident::getDescriere() const { return descriere; }
int Incident::getImpactMinute() const { return impactMinute; }

std::string Incident::getTipString() const {
    switch (tip) {
        case TipIncident::TRAFIC_INTENS: return "Trafic Intens";
        case TipIncident::INTARZIERE: return "Intarziere";
        case TipIncident::DEFECTIUNE: return "Defectiune";
        case TipIncident::ACCIDENT: return "Accident";
        case TipIncident::METEO_NEFAVORABIL: return "Meteo";
        case TipIncident::LUCRARI_DRUM: return "Lucrari";
        default: return "Altele";
    }
}

void Incident::setImpactMinute(int minute) {
    if (minute >= 0) this->impactMinute = minute;
}

void Incident::setDescriere(const std::string& desc) {
    if (!desc.empty()) this->descriere = desc;
}

bool Incident::operator==(const Incident& other) const {
    return (this->tip == other.tip && this->impactMinute == other.impactMinute && this->descriere == other.descriere);
}

bool Incident::operator<(const Incident& other) const {
    return this->impactMinute < other.impactMinute;
}

std::ostream& operator<<(std::ostream& os, const Incident& i) {
    os << "[" << i.getTipString() << "] " << i.descriere << " | Impact: " << i.impactMinute << " min";
    return os;
}