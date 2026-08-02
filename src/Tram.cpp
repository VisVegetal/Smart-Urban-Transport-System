#include "../include/Tram.hpp"

#include <memory>

Tram::Tram(int id, int capacity, int trafficLightCount, bool intersectionPriority)
    : Vehicle(id, capacity),
      trafficLightCount(trafficLightCount),
      intersectionPriority(intersectionPriority) {}

double Tram::calculateTime(const Route& route) const {
    double speed = 40.0; // km/h
    double time = route.getDistance() / speed;

    if (intersectionPriority) {
        // minimal delays thanks to priority
        time += trafficLightCount * 0.005;
    } else {
        // larger delays without priority
        time += trafficLightCount * 0.02;
    }

    return time;
}

int Tram::getTrafficLightCount() const {
    return trafficLightCount;
}

bool Tram::hasPriority() const {
    return intersectionPriority;
}

std::string Tram::getType() const {
    return "Tram";
}

std::string Tram::describe() const {
    return "Tram | ID " + std::to_string(id) +
           " | Capacity " + std::to_string(capacity);
}

std::unique_ptr<Vehicle> Tram::clone() const {
    return std::make_unique<Tram>(*this);
}
