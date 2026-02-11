#ifndef INCIDENT_HPP
#define INCIDENT_HPP

#include <string>
#include <iostream>

enum class TipIncident {
    TRAFIC_INTENS,
    INTARZIERE,
    DEFECTIUNE,
    ACCIDENT,
    METEO_NEFAVORABIL,
    LUCRARI_DRUM
};

class Incident {
private:
    TipIncident tip;
    std::string descriere;
    int impactMinute;
    std::string dataRaportarii;

public:
    Incident();
    Incident(TipIncident tip, std::string descriere, int impactMinute, std::string data = "11-02-2026");

    Incident(const Incident& other);
    Incident& operator=(const Incident& other);
    ~Incident() = default;

    [[nodiscard]] TipIncident getTip() const;
    [[nodiscard]] const std::string& getDescriere() const;
    [[nodiscard]] int getImpactMinute() const;
    [[nodiscard]] std::string getTipString() const;

    void setImpactMinute(int minute);
    void setDescriere(const std::string& desc);

    bool operator==(const Incident& other) const;
    bool operator<(const Incident& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Incident& i);
};

#endif