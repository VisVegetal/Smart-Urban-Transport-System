#ifndef INCIDENT_HPP
#define INCIDENT_HPP

#include <string>
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
    std::string descriere;
    int impactMinute;

public:
    Incident(TipIncident tip,
             const std::string& descriere,
             int impactMinute)
        : tip(tip), descriere(descriere), impactMinute(impactMinute) {
        if (impactMinute < 0) {
            throw ValoareInvalidaException("Impact negativ.");
        }
    }

    TipIncident getTip() const { return tip; }
    const std::string& getDescriere() const { return descriere; }
    int getImpactMinute() const { return impactMinute; }
};

#endif
