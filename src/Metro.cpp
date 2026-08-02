#include "../include/Metro.hpp"

#include <memory>

Metro::Metro(int id, int capacity, int intervalMinutes, bool automaticSystem)
    : Vehicle(id, capacity),
      intervalMinutes(intervalMinutes),
      automaticSystem(automaticSystem) {}

double Metro::calculateTime(const Route& route) const {
    double speed = 60.0;
    double time = route.getDistance() / speed;

    // average waiting time
    time += (intervalMinutes / 60.0) / 2.0;

    // the automatic system is more efficient
    if (automaticSystem) {
        time *= 0.95;
    }

    return time;
}

int Metro::getIntervalMinutes() const {
    return intervalMinutes;
}

bool Metro::isAutomatic() const {
    return automaticSystem;
}

std::string Metro::getType() const {
    return "Metro";
}

std::string Metro::describe() const {
    return "Metro | ID " + std::to_string(id) +
           " | Capacity " + std::to_string(capacity);
}

std::unique_ptr<Vehicle> Metro::clone() const {
    return std::make_unique<Metro>(*this);
}
