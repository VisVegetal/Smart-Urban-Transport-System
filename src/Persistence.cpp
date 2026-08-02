#include "../include/Persistence.hpp"
#include "../include/Exceptions.hpp"
#include "../include/VehicleFactory.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

void Persistence::saveSystem(const Dispatcher& d, const std::string& fileName) {
    std::ofstream f(fileName);
    if (!f.is_open()) throw TransportException("Could not open file for saving.");

    f << "VEHICLES_START\n";
    for (const auto v : d.getVehicles()) {
        int typeInt = (v->getType() == "Bus") ? 1 : (v->getType() == "Tram") ? 2 : 3;
        f << typeInt << " " << v->getId() << " " << v->getCapacity() << "\n";
    }
    f << "VEHICLES_END\n";

    f << "ROUTES_START\n";
    for (const auto& r : d.getRoutes()) {
        f << r.getName() << ";" << r.getDistance() << "\n";
    }
    f << "ROUTES_END\n";

    f.close();
}

void Persistence::loadSystem(Dispatcher& d, const std::string& fileName) {
    std::ifstream f(fileName);
    if (!f.is_open()) throw TransportException("Data file does not exist.");

    std::string line;
    std::string currentSection;

    while (std::getline(f, line)) {
        if (line == "VEHICLES_START") { currentSection = "VEHICLES"; continue; }
        if (line == "ROUTES_START") { currentSection = "ROUTES"; continue; }
        if (line.find("_END") != std::string::npos) { currentSection = ""; continue; }

        if (currentSection == "VEHICLES") {
            std::stringstream ss(line);
            int type, id, capacity;
            if (ss >> type >> id >> capacity) {
                if (!d.hasVehicle(id)) {
                    d.addVehicle(VehicleFactory::createVehicle(type, id, capacity));
                }
            }
        }
        else if (currentSection == "ROUTES") {
            size_t delim = line.find(';');
            if (delim != std::string::npos) {
                std::string name = line.substr(0, delim);
                double distance = std::stod(line.substr(delim + 1));
                if (!d.hasRoute(name)) d.addRoute(Route(name, distance));
            }
        }
    }
    f.close();
}

bool Persistence::isFileValid(const std::string& fileName) {
    std::ifstream f(fileName);
    if (!f.is_open()) return false;

    std::string firstLine;
    std::getline(f, firstLine);
    f.close();

    return (firstLine == "VEHICLES_START");
}
