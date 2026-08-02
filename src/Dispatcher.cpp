#include "../include/Dispatcher.hpp"
#include "../include/Exceptions.hpp"
#include "../include/Logger.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <utility>

Dispatcher::Dispatcher() = default;

Dispatcher::~Dispatcher() noexcept = default;

Dispatcher::Dispatcher(const Dispatcher& other)
    : routes(other.routes),
      incidents(other.incidents),
      maintenance(other.maintenance),
      ticketingSystem(other.ticketingSystem) {
    vehicles.reserve(other.vehicles.size());
    for (const auto& vehicle : other.vehicles) {
        vehicles.push_back(vehicle->clone());
    }
}

Dispatcher::Dispatcher(Dispatcher&& other) noexcept = default;

Dispatcher& Dispatcher::operator=(const Dispatcher& other) {
    if (this != &other) {
        Dispatcher tmp(other);
        *this = std::move(tmp);
    }
    return *this;
}

Dispatcher& Dispatcher::operator=(Dispatcher&& other) noexcept = default;

void Dispatcher::addVehicle(std::unique_ptr<Vehicle> vehicle) {
    if (!vehicle) {
        throw VehicleException("Received a null vehicle pointer.");
    }
    const int id = vehicle->getId();
    if (hasVehicle(id)) {
        throw VehicleException("Duplicate vehicle ID!");
    }
    vehicles.push_back(std::move(vehicle));
    Logger::getInstance().log(LogLevel::INFO,
        "Vehicle ID " + std::to_string(id) + " added.");
}

bool Dispatcher::hasVehicle(int id) const {
    return std::ranges::any_of(vehicles, [id](const std::unique_ptr<Vehicle>& vehicle) {
        return vehicle->getId() == id;
    });
}

void Dispatcher::removeVehicle(int id) {
    auto it = std::ranges::find_if(vehicles, [id](const std::unique_ptr<Vehicle>& vehicle) {
        return vehicle->getId() == id;
    });
    if (it != vehicles.end()) {
        vehicles.erase(it);
        Logger::getInstance().log(LogLevel::INFO,
            "Vehicle ID " + std::to_string(id) + " deleted.");
    } else {
        throw VehicleException("Vehicle not found for deletion.");
    }
}

void Dispatcher::showVehicles() const {
    if (vehicles.empty()) {
        std::cout << "The fleet is empty.\n";
        return;
    }
    std::ranges::for_each(vehicles, [this](const std::unique_ptr<Vehicle>& vehicle) {
        std::cout << vehicle->getType() << " | ID: " << vehicle->getId()
                  << " | Status: " << maintenance.getStatusDetails(vehicle->getId()) << "\n";
    });
}

void Dispatcher::addRoute(const Route& route) {
    if (hasRoute(route.getName())) {
        throw RouteException("Route already exists.");
    }
    routes.push_back(route);
}

void Dispatcher::showRoutes() const {
    if (routes.empty()) {
        std::cout << "No routes configured.\n";
        return;
    }
    std::ranges::for_each(routes, [](const Route& route) {
        std::cout << "Route: " << route.getName() << " | Distance: " << route.getDistance() << " km\n";
    });
}

bool Dispatcher::hasRoute(const std::string& name) const {
    return std::ranges::any_of(routes, [&name](const Route& route) {
        return route.getName() == name;
    });
}

void Dispatcher::removeRoute(const std::string& name) {
    auto it = std::ranges::find_if(routes, [&name](const Route& route) {
        return route.getName() == name;
    });
    if (it != routes.end()) {
        routes.erase(it);
    } else {
        throw RouteException("Route does not exist.");
    }
}

const Route* Dispatcher::findRoute(const std::string& name) const {
    auto it = std::ranges::find_if(routes, [&name](const Route& route) {
        return route.getName() == name;
    });
    return (it != routes.end()) ? &(*it) : nullptr;
}

void Dispatcher::addIncident(const Incident& incident) {
    incidents.push_back(incident);
    Logger::getInstance().log(LogLevel::WARNING,
        "New incident: " + incident.getDescription());
}

void Dispatcher::showIncidents() const {
    if (incidents.empty()) {
        std::cout << "No incidents reported.\n";
        return;
    }
    for (const auto& i : incidents) {
        std::cout << "Alert: " << i.getDescription() << " | +" << i.getImpactMinutes() << " min\n";
    }
}

int Dispatcher::calculateTotalImpact() const {
    return std::accumulate(incidents.begin(), incidents.end(), 0,
        [](int acc, const Incident& i) { return acc + i.getImpactMinutes(); });
}

double Dispatcher::simulateTrip(int vehicleId, const std::string& routeName) {
    if (!maintenance.canRun(vehicleId)) {
        throw TransportException("Vehicle is in service!");
    }
    const Route* route = findRoute(routeName);
    if (!route) throw RouteException("Route not found.");
    auto it = std::ranges::find_if(vehicles, [vehicleId](const std::unique_ptr<Vehicle>& vehicle) {
        return vehicle->getId() == vehicleId;
    });
    if (it == vehicles.end()) throw VehicleException("Vehicle does not exist.");
    double time = (*it)->calculateTime(*route);
    time += (calculateTotalImpact() / 60.0);
    maintenance.updateMileage(vehicleId, static_cast<int>(route->getDistance()));
    return time;
}

double Dispatcher::calculateTotalTime(const std::string& routeName) const {
    const Route* route = findRoute(routeName);
    if (!route) throw RouteException("Route does not exist.");
    if (vehicles.empty()) throw VehicleException("No vehicles available.");

    double minimumTime = std::numeric_limits<double>::max();
    for (const auto& vehicle : vehicles) {
        double t = vehicle->calculateTime(*route);
        if (t < minimumTime) minimumTime = t;
    }
    return minimumTime + (calculateTotalImpact() / 60.0);
}

void Dispatcher::sellTicket(bool reduced, double price, double discount) {
    if (reduced) ticketingSystem.issueReducedTicket(price, discount);
    else ticketingSystem.issueFullTicket(price);
}

double Dispatcher::calculateTotalRevenue() const {
    return ticketingSystem.calculateRevenue();
}

void Dispatcher::generateActivityReport() const {
    std::cout << "\n========== ACTIVITY REPORT ==========\n";
    std::cout << "Vehicles: " << vehicles.size() << "\n";
    std::cout << "Routes: " << routes.size() << "\n";
    std::cout << "Revenue: " << calculateTotalRevenue() << " RON\n";
    std::cout << "=====================================\n";
}

Maintenance& Dispatcher::getMaintenance() { return maintenance; }
const std::vector<Route>& Dispatcher::getRoutes() const { return routes; }
const std::vector<Incident>& Dispatcher::getIncidents() const { return incidents; }
