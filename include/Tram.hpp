#ifndef TRAM_HPP
#define TRAM_HPP

#include "Vehicle.hpp"

class Tram : public Vehicle {
private:
    int trafficLightCount;      // number of traffic lights along the route
    bool intersectionPriority;  // whether the tram has intersection priority

public:
    Tram(int id,
         int capacity,
         int trafficLightCount = 8,
         bool intersectionPriority = false);

    [[nodiscard]] double calculateTime(const Route& route) const override;
    [[nodiscard]] std::string getType() const override;

    // Generic description
    [[nodiscard]] std::string describe() const override;

    [[nodiscard]] int getTrafficLightCount() const;
    [[nodiscard]] bool hasPriority() const;

    [[nodiscard]] std::unique_ptr<Vehicle> clone() const override;
};

#endif
