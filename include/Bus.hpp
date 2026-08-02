#ifndef BUS_HPP
#define BUS_HPP

#include "Vehicle.hpp"

class Bus : public Vehicle {
private:
    bool dedicatedLane;      // whether the bus has a dedicated lane
    int stopCount;           // number of stops along the route
    int trafficLightCount;   // number of traffic lights along the route

public:
    Bus(int id,
        int capacity,
        bool dedicatedLane = false,
        int stopCount = 10,
        int trafficLightCount = 12);

    // Travel time considering stops and traffic lights
    [[nodiscard]] double calculateTime(const Route& route) const override;

    [[nodiscard]] bool hasDedicatedLane() const;
    [[nodiscard]] int getStopCount() const;
    [[nodiscard]] int getTrafficLightCount() const;

    [[nodiscard]] std::string getType() const override;

    // Generic description
    [[nodiscard]] std::string describe() const override;

    [[nodiscard]] std::unique_ptr<Vehicle> clone() const override;
};

#endif
