#ifndef VEHICLE_FACTORY_HPP
#define VEHICLE_FACTORY_HPP

#include <memory>

#include "Bus.hpp"
#include "Exceptions.hpp"
#include "Metro.hpp"
#include "Tram.hpp"
#include "Vehicle.hpp"

// Factory Method for creating vehicles
class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> createVehicle(
        int type,
        int id,
        int capacity
    ) {
        switch (type) {
            case 1:
                return std::make_unique<Bus>(id, capacity);
            case 2:
                return std::make_unique<Tram>(id, capacity);
            case 3:
                return std::make_unique<Metro>(id, capacity);
            default:
                throw TransportException("Invalid vehicle type.");
        }
    }
};

#endif
