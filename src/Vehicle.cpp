#include "../include/Vehicle.hpp"
#include "../include/Exceptions.hpp"

int Vehicle::vehicleCount = 0;

Vehicle::Vehicle(int id, int capacity)
    : id(id), capacity(capacity) {
    if (capacity <= 0) {
        throw VehicleException("Invalid capacity: must be positive.");
    }
    ++vehicleCount;
}

Vehicle::Vehicle(const Vehicle& other)
    : id(other.id), capacity(other.capacity) {
    ++vehicleCount;
}

Vehicle::~Vehicle() {
    --vehicleCount;
}

int Vehicle::getId() const { return id; }
int Vehicle::getCapacity() const { return capacity; }

int Vehicle::getVehicleCount() { return vehicleCount; }
