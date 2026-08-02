#include "../include/Station.hpp"
#include "../include/Exceptions.hpp"

#include <iostream>

Station::Station(const std::string& name) : name(name) {
    if (name.empty()) {
        throw InvalidValueException("Invalid station name.");
    }
}

const std::string& Station::getName() const { return name; }

// Adds a route to the station's list (duplicates are ignored)
void Station::addRoute(const std::string& routeName) {
    for (const auto& r : routes) {
        if (r == routeName) {
            return; // route already registered
        }
    }
    routes.push_back(routeName);
}

// Prints the station and its associated routes
void Station::show() const {
    std::cout << "Station: " << name << "\n";
    std::cout << "Available routes: ";

    if (routes.empty()) {
        std::cout << "None";
    } else {
        for (const auto& r : routes) {
            std::cout << r << " ";
        }
    }

    std::cout << "\n";
}
