#include "../include/Maintenance.hpp"

#include <iostream>
#include <ranges>

void Maintenance::updateMileage(int id, int km) {
    kilometersDriven[id] += km;
    if (kilometersDriven[id] >= MAINTENANCE_THRESHOLD && fleetStatus[id] == VehicleState::OPERATIONAL) {
        fleetStatus[id] = VehicleState::SERVICE_DUE;
    }
}

void Maintenance::sendToService(int id, const std::string& reason) {
    fleetStatus[id] = VehicleState::IN_SERVICE;
    serviceHistory[id].push_back("Service entry: " + reason);
}

void Maintenance::repairVehicle(int id) {
    fleetStatus[id] = VehicleState::OPERATIONAL;
    kilometersDriven[id] = 0;
    serviceHistory[id].emplace_back("Repair completed. Mileage reset.");
}

bool Maintenance::canRun(int id) const {
    if (!fleetStatus.contains(id)) return true;
    return fleetStatus.at(id) == VehicleState::OPERATIONAL;
}

std::string Maintenance::getStatusDetails(int id) const {
    if (!fleetStatus.contains(id)) return "NEW/UNREGISTERED";

    VehicleState s = fleetStatus.at(id);
    std::string txt;
    switch (s) {
        case VehicleState::OPERATIONAL: txt = "OPERATIONAL"; break;
        case VehicleState::SERVICE_DUE: txt = "SERVICE DUE"; break;
        case VehicleState::IN_SERVICE: txt = "IN SERVICE"; break;
        case VehicleState::RETIRED: txt = "RETIRED"; break;
        default: txt = "UNKNOWN"; break;
    }

    int km = kilometersDriven.contains(id) ? kilometersDriven.at(id) : 0;
    return txt + " (" + std::to_string(km) + " km)";
}

void Maintenance::generateTechnicalReport() const {
    std::cout << "\n========== FLEET TECHNICAL REPORT ==========\n";
    for (int id : kilometersDriven | std::views::keys) {
        std::cout << "ID: " << id << " | Status: " << getStatusDetails(id) << "\n";
        if (serviceHistory.contains(id)) {
            for (const auto& log : serviceHistory.at(id)) {
                std::cout << "  - " << log << "\n";
            }
        }
    }
    std::cout << "============================================\n";
}

void Maintenance::addTechnicalNote(int id, const std::string& note) {
    serviceHistory[id].push_back("Note: " + note);
}

int Maintenance::getKilometers(int id) const {
    if (kilometersDriven.contains(id)) return kilometersDriven.at(id);
    return 0;
}
