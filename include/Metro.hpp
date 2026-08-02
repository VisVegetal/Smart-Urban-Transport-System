#ifndef METRO_HPP
#define METRO_HPP

#include "Vehicle.hpp"

class Metro : public Vehicle {
private:
    int intervalMinutes;  // interval between trains
    bool automaticSystem; // whether the train control system is automatic

public:
    Metro(int id,
          int capacity,
          int intervalMinutes = 4,
          bool automaticSystem = true);

    [[nodiscard]] double calculateTime(const Route& route) const override;

    [[nodiscard]] int getIntervalMinutes() const;
    [[nodiscard]] bool isAutomatic() const;

    [[nodiscard]] std::string getType() const override;

    // Generic description
    [[nodiscard]] std::string describe() const override;

    [[nodiscard]] std::unique_ptr<Vehicle> clone() const override;
};

#endif
