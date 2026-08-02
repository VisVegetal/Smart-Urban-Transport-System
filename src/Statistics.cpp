#include "../include/Statistics.hpp"
#include "../include/Dispatcher.hpp"
#include "../include/Vehicle.hpp"
#include "../include/Bus.hpp"
#include "../include/Tram.hpp"
#include "../include/Metro.hpp"
#include "../include/Exceptions.hpp"
#include "../include/Station.hpp"
#include "../include/StatisticsSeries.hpp"

#include <iostream>
#include <limits>

// Fastest vehicle for a given route
const Vehicle* Statistics::fastestVehicle(
    const Dispatcher& d,
    const std::string& routeName
) {
    const Route* route = d.findRoute(routeName);
    if (!route) {
        throw RouteException("Route does not exist for statistics.");
    }

    const Vehicle* fastestVehicle = nullptr;
    double minimumTime = std::numeric_limits<double>::max();

    for (const auto v : d.getVehicles()) {
        double time = v->calculateTime(*route);
        if (time < minimumTime) {
            minimumTime = time;
            fastestVehicle = v;
        }
    }

    return fastestVehicle;
}

// Vehicle with the highest capacity
const Vehicle* Statistics::maxCapacityVehicle(
    const Dispatcher& d
) {
    const Vehicle* maxVehicle = nullptr;
    int maxCapacity = -1;

    for (const auto v : d.getVehicles()) {
        if (v->getCapacity() > maxCapacity) {
            maxCapacity = v->getCapacity();
            maxVehicle = v;
        }
    }

    return maxVehicle;
}

// Average travel time for a route
double Statistics::averageTimeOnRoute(
    const Dispatcher& d,
    const std::string& routeName
) {
    const Route* route = d.findRoute(routeName);
    if (!route) {
        throw RouteException("Route does not exist for average time calculation.");
    }

    StatisticsSeries<double> stat;

    for (const auto v : d.getVehicles()) {
        stat.add(v->calculateTime(*route));
    }

    return stat.average();
}

// Summary report of the system
void Statistics::generalReport(const Dispatcher& d) {
    std::cout << "\n===== GENERAL SYSTEM REPORT =====\n";

    std::cout << "Active vehicles in system: "
              << d.getVehicles().size() << "\n";

    std::cout << "Live vehicles (static counter): "
              << Vehicle::getVehicleCount() << "\n";

    std::cout << "Active incidents: "
              << d.getIncidents().size() << "\n";

    Station s1("Central");
    Station s2("Airport");

    for (const auto& r : d.getRoutes()) {
        s1.addRoute(r.getName());
        s2.addRoute(r.getName());
    }

    s1.show();
    s2.show();

    std::cout << "================================\n";
}

// Distribution of vehicles by type
void Statistics::vehicleDistribution(const Dispatcher& d) {
    int buses = 0;
    int trams = 0;
    int metros = 0;

    std::cout << "\n===== VEHICLE DISTRIBUTION BY TYPE =====\n";

    for (const auto v : d.getVehicles()) {
        if (const auto* a = dynamic_cast<const Bus*>(v)) {
            ++buses;
            std::cout << "[Bus] ID " << a->getId()
                      << " | Capacity: " << a->getCapacity()
                      << " | Dedicated lane: "
                      << (a->hasDedicatedLane() ? "YES" : "NO") << "\n";
        }
        else if (const auto* t = dynamic_cast<const Tram*>(v)) {
            ++trams;
            std::cout << "[Tram] ID " << t->getId()
                      << " | Capacity: " << t->getCapacity()
                      << " | Intersection priority: "
                      << (t->hasPriority() ? "YES" : "NO") << "\n";
        }
        else if (const auto* m = dynamic_cast<const Metro*>(v)) {
            ++metros;
            std::cout << "[Metro] ID " << m->getId()
                      << " | Capacity: " << m->getCapacity()
                      << " | Interval: " << m->getIntervalMinutes()
                      << " min | Automatic system: "
                      << (m->isAutomatic() ? "YES" : "NO") << "\n";
        }
    }

    std::cout << "\n----- SUMMARY -----\n";
    std::cout << "Buses: " << buses << "\n";
    std::cout << "Trams: " << trams << "\n";
    std::cout << "Metro trains: " << metros << "\n";
    std::cout << "===============================\n";
}

double Statistics::averageIncidentImpact(const Dispatcher& d) {
    StatisticsSeries<int> stat;
    for (const auto& i : d.getIncidents()) {
        stat.add(i.getImpactMinutes());
    }
    return stat.average();
}

void Statistics::detailedReport(const Dispatcher& d) {
    std::cout << "\n===== DETAILED SYSTEM REPORT =====\n";

    for (const auto v : d.getVehicles()) {
        if (const auto* a = dynamic_cast<const Bus*>(v)) {
            std::cout << "[Bus] ID " << a->getId()
                      << " | Capacity: " << a->getCapacity()
                      << " | Stops: " << a->getStopCount()
                      << " | Traffic lights: " << a->getTrafficLightCount()
                      << " | Dedicated lane: "
                      << (a->hasDedicatedLane() ? "YES" : "NO") << "\n";
        }
        else if (const auto* t = dynamic_cast<const Tram*>(v)) {
            std::cout << "[Tram] ID " << t->getId()
                      << " | Capacity: " << t->getCapacity()
                      << " | Traffic lights: " << t->getTrafficLightCount()
                      << " | Priority: "
                      << (t->hasPriority() ? "YES" : "NO") << "\n";
        }
        else if (const auto* m = dynamic_cast<const Metro*>(v)) {
            std::cout << "[Metro] ID " << m->getId()
                      << " | Capacity: " << m->getCapacity()
                      << " | Interval: " << m->getIntervalMinutes()
                      << " min | Automatic: "
                      << (m->isAutomatic() ? "YES" : "NO") << "\n";
        }
    }

    std::cout << "Average incident impact: "
              << averageIncidentImpact(d)
              << " minutes\n";

    std::cout << "=================================\n";
}

void Statistics::recommendOptimalVehicle(const Dispatcher& d, const std::string& routeName) {
    const Route* route = d.findRoute(routeName);
    if (!route) throw RouteException("Route does not exist for smart analysis.");

    const Vehicle* recommended = nullptr;
    double shortestTime = std::numeric_limits<double>::max();

    std::cout << "\n--- SMART ROUTING ANALYSIS FOR: " << routeName << " ---\n";

    for (const auto v : d.getVehicles()) {
        double time = v->calculateTime(*route);
        time += d.calculateTotalImpact() / 60.0;

        std::cout << "> " << v->getType() << " ID " << v->getId()
                  << " | Estimated time: " << time << " hours\n";

        if (time < shortestTime) {
            shortestTime = time;
            recommended = v;
        }
    }

    if (recommended) {
        std::cout << "\n[SYSTEM DECISION]: Based on current conditions, we recommend "
                  << recommended->getType() << " (ID " << recommended->getId() << ")\n";
    }
}
