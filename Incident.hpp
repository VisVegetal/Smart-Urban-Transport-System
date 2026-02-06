#ifndef INCIDENT_HPP
#define INCIDENT_HPP

#include <string>
#include <utility>
#include "Exceptii.hpp"

enum class TipIncident {
    TRAFIC_INTENS,
    INTARZIERE,
    DEFECTIUNE,
    ACCIDENT
};

class Incident {
private:
    TipIncident tip;
    std::string descriere; //descriere textuala
    int impactMinute; //impactul in minute asupra traficului

public:
    Incident(TipIncident tip,
             std::string  descriere,
             int impactMinute)
        : tip(tip), descriere(std::move(descriere)), impactMinute(impactMinute) {
        if (impactMinute < 0) {
            throw ValoareInvalidaException("Impact negativ.");
        }
    }

    [[nodiscard]] TipIncident getTip() const { return tip; }
    [[nodiscard]] const std::string& getDescriere() const { return descriere; }
    [[nodiscard]] int getImpactMinute() const { return impactMinute; }
};

#endif
