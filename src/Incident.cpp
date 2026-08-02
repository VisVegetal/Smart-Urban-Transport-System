#include "../include/Incident.hpp"
#include "../include/Exceptions.hpp"

#include <utility>

Incident::Incident()
    : type(IncidentType::HEAVY_TRAFFIC),
      description("Unknown"),
      impactMinutes(0) {}

Incident::Incident(IncidentType type, std::string description, int impactMinutes)
    : type(type),
      description(std::move(description)),
      impactMinutes(impactMinutes) {
    if (impactMinutes < 0) {
        throw InvalidValueException("Impact cannot be negative.");
    }
}

IncidentType Incident::getType() const { return type; }
const std::string& Incident::getDescription() const { return description; }
int Incident::getImpactMinutes() const { return impactMinutes; }

std::string Incident::getTypeString() const {
    switch (type) {
        case IncidentType::HEAVY_TRAFFIC: return "Heavy Traffic";
        case IncidentType::DELAY: return "Delay";
        case IncidentType::BREAKDOWN: return "Breakdown";
        case IncidentType::ACCIDENT: return "Accident";
        case IncidentType::BAD_WEATHER: return "Weather";
        case IncidentType::ROAD_WORKS: return "Road Works";
        default: return "Other";
    }
}

bool Incident::operator==(const Incident& other) const {
    return this->type == other.type &&
           this->impactMinutes == other.impactMinutes &&
           this->description == other.description;
}

bool Incident::operator<(const Incident& other) const {
    return this->impactMinutes < other.impactMinutes;
}

std::ostream& operator<<(std::ostream& os, const Incident& i) {
    os << "[" << i.getTypeString() << "] " << i.description
       << " | Impact: " << i.impactMinutes << " min";
    return os;
}
