#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <memory>
#include <string>

#include "Route.hpp"

class Vehicle {
protected:
    int id;
    int capacity;
    static int vehicleCount;

public:
    Vehicle(int id, int capacity);
    Vehicle(const Vehicle& other);
    virtual ~Vehicle();

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getCapacity() const;

    // Travel time calculation for a given route
    [[nodiscard]] virtual double calculateTime(const Route& route) const = 0;

    // Vehicle type identifier
    [[nodiscard]] virtual std::string getType() const = 0;

    // Generic description
    [[nodiscard]] virtual std::string describe() const = 0;

    // Polymorphic deep copy
    [[nodiscard]] virtual std::unique_ptr<Vehicle> clone() const = 0;

    static int getVehicleCount();
};

#endif
