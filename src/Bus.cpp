#include "../include/Bus.hpp"

#include <memory>

Bus::Bus(int id, int capacity, bool dedicatedLane, int stopCount, int trafficLightCount)
    : Vehicle(id, capacity),
      dedicatedLane(dedicatedLane),
      stopCount(stopCount),
      trafficLightCount(trafficLightCount) {}

double Bus::calculateTime(const Route& route) const {
    double speed = 30.0; // km/h
    double time = route.getDistance() / speed; // in hours

    // delays caused by stops
    time += stopCount * 0.01;

    // delays caused by traffic lights
    time += trafficLightCount * 0.015;

    // extra traffic delay when there is no dedicated lane
    if (!dedicatedLane) {
        time *= 1.2;
    }

    return time;
}

bool Bus::hasDedicatedLane() const {
    return dedicatedLane;
}

int Bus::getStopCount() const {
    return stopCount;
}

int Bus::getTrafficLightCount() const {
    return trafficLightCount;
}

std::string Bus::getType() const {
    return "Bus";
}

std::string Bus::describe() const {
    return "Bus | ID " + std::to_string(id) +
           " | Capacity " + std::to_string(capacity);
}

std::unique_ptr<Vehicle> Bus::clone() const {
    return std::make_unique<Bus>(*this);
}
