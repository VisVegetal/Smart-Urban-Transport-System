#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "Incident.hpp"
#include "Maintenance.hpp"
#include "Route.hpp"
#include "Ticketing.hpp"
#include "Vehicle.hpp"

class Dispatcher {
private:
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    std::vector<Route> routes;
    std::vector<Incident> incidents;

    Maintenance maintenance;
    TicketingSystem ticketingSystem;

public:
    Dispatcher();
    ~Dispatcher() noexcept;
    Dispatcher(const Dispatcher& other);
    Dispatcher& operator=(const Dispatcher& other);
    Dispatcher(Dispatcher&& other) noexcept;
    Dispatcher& operator=(Dispatcher&& other) noexcept;

    void addVehicle(std::unique_ptr<Vehicle> vehicle);
    [[nodiscard]] bool hasVehicle(int id) const;
    void removeVehicle(int id);
    void showVehicles() const;

    void addRoute(const Route& route);
    void showRoutes() const;
    [[nodiscard]] bool hasRoute(const std::string& name) const;
    void removeRoute(const std::string& name);
    [[nodiscard]] const Route* findRoute(const std::string& name) const;

    void addIncident(const Incident& incident);
    void showIncidents() const;
    [[nodiscard]] int calculateTotalImpact() const;

    double simulateTrip(int vehicleId, const std::string& routeName);
    [[nodiscard]] double calculateTotalTime(const std::string& routeName) const;

    void sellTicket(bool reduced, double price, double discount = 0.0);
    [[nodiscard]] double calculateTotalRevenue() const;

    void generateActivityReport() const;

    Maintenance& getMaintenance();

    // Read-only, type-erased view of the fleet
    [[nodiscard]] auto getVehicles() const {
        return vehicles | std::views::transform(
            [](const std::unique_ptr<Vehicle>& vehicle) -> const Vehicle* {
                return vehicle.get();
            });
    }
    [[nodiscard]] const std::vector<Route>& getRoutes() const;
    [[nodiscard]] const std::vector<Incident>& getIncidents() const;
};

#endif
