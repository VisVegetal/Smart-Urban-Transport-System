#ifndef INCIDENT_HPP
#define INCIDENT_HPP

#include <ostream>
#include <string>

enum class IncidentType {
    HEAVY_TRAFFIC,
    DELAY,
    BREAKDOWN,
    ACCIDENT,
    BAD_WEATHER,
    ROAD_WORKS
};

class Incident {
private:
    IncidentType type;
    std::string description;
    int impactMinutes;

public:
    Incident();
    Incident(IncidentType type, std::string description, int impactMinutes);

    Incident(const Incident& other) = default;
    Incident& operator=(const Incident& other) = default;
    ~Incident() = default;

    [[nodiscard]] IncidentType getType() const;
    [[nodiscard]] const std::string& getDescription() const;
    [[nodiscard]] int getImpactMinutes() const;
    [[nodiscard]] std::string getTypeString() const;

    bool operator==(const Incident& other) const;
    bool operator<(const Incident& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Incident& i);
};

#endif
