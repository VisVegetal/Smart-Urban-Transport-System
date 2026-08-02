#include <iostream>
#include <limits>
#include <string>

#include "../include/Dispatcher.hpp"
#include "../include/Incident.hpp"
#include "../include/Logger.hpp"
#include "../include/Maintenance.hpp"
#include "../include/Persistence.hpp"
#include "../include/Statistics.hpp"
#include "../include/Vehicle.hpp"
#include "../include/VehicleFactory.hpp"

void clearInput() {
    if (std::cin.eof()) return;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Dispatcher dispatcher;

    std::string userInput;

    while (true) {
        std::cout << "\n=== URBAN TRANSPORT MANAGEMENT SYSTEM ===\n";
        std::cout << "1. Add Vehicle | 2. Delete Vehicle | 3. Show Vehicles\n";
        std::cout << "4. Add Route | 5. Show Routes | 16. Delete Route\n";
        std::cout << "6. Add Incident | 7. Show Incidents | 8. Total Route Time\n";
        std::cout << "9. Show Logs | 10. Save Logs | 11. Simulate Trip\n";
        std::cout << "12. Save System | 13. Load System | 17. Validate File\n";
        std::cout << "14. Detailed Report | 15. Vehicle Distribution | 18. General Report\n";
        std::cout << "19. Fastest Vehicle | 20. Max Capacity | 21. Average Route Time\n";
        std::cout << "22. Activity Report | 23. Total Revenue | 24. Smart Recommendation\n";
        std::cout << "25. Send to Service | 26. Repair Vehicle | 27. Technical Report\n";
        std::cout << "28. Sell Ticket | 0. Exit\n";
        std::cout << "Your option: ";

        if (!(std::cin >> userInput)) {
            break;
        }

        int option;
        try {
            option = std::stoi(userInput);
        } catch (...) {
            if (std::cin.eof()) break;
            std::cout << "Invalid option! Please enter a number.\n";
            clearInput();
            continue;
        }

        if (option == 0) break;

        try {
            switch (option) {
            case 1: {
                int type, id, capacity;
                if (!(std::cin >> type >> id >> capacity)) { clearInput(); break; }
                dispatcher.addVehicle(VehicleFactory::createVehicle(type, id, capacity));
                break;
            }
            case 2: {
                int id;
                if (!(std::cin >> id)) { clearInput(); break; }
                dispatcher.removeVehicle(id);
                break;
            }
            case 3:
                dispatcher.showVehicles();
                break;
            case 4: {
                std::string name;
                double distance;
                clearInput();
                if (!std::getline(std::cin, name) || name.empty()) break;
                if (!(std::cin >> distance)) { clearInput(); break; }
                dispatcher.addRoute(Route(name, distance));
                break;
            }
            case 5:
                dispatcher.showRoutes();
                break;
            case 6: {
                int type, impact;
                std::string description;
                if (!(std::cin >> type >> impact)) { clearInput(); break; }
                clearInput();
                if (!std::getline(std::cin, description)) break;
                dispatcher.addIncident(
                    Incident(static_cast<IncidentType>(type), description, impact));
                break;
            }
            case 7:
                dispatcher.showIncidents();
                break;
            case 8: {
                std::string name;
                clearInput();
                if (!std::getline(std::cin, name)) break;
                std::cout << "Time: " << dispatcher.calculateTotalTime(name) << "\n";
                break;
            }
            case 9:
                Logger::getInstance().showLogs();
                break;
            case 10:
                Logger::getInstance().saveToFile("audit.log");
                break;
            case 11: {
                int id;
                std::string name;
                if (!(std::cin >> id)) { clearInput(); break; }
                clearInput();
                if (!std::getline(std::cin, name)) break;
                std::cout << "Result: " << dispatcher.simulateTrip(id, name) << "\n";
                break;
            }
            case 12:
                Persistence::saveSystem(dispatcher, "system.txt");
                break;
            case 13:
                Persistence::loadSystem(dispatcher, "system.txt");
                break;
            case 14:
                Statistics::detailedReport(dispatcher);
                break;
            case 15:
                Statistics::vehicleDistribution(dispatcher);
                break;
            case 16: {
                std::string name;
                clearInput();
                if (!std::getline(std::cin, name)) break;
                dispatcher.removeRoute(name);
                break;
            }
            case 17:
                if (Persistence::isFileValid("system.txt")) std::cout << "File is valid.\n";
                break;
            case 18:
                Statistics::generalReport(dispatcher);
                break;
            case 19: {
                std::string name;
                clearInput();
                if (!std::getline(std::cin, name)) break;
                if (const auto* v = Statistics::fastestVehicle(dispatcher, name))
                    std::cout << "ID: " << v->getId() << "\n";
                break;
            }
            case 20:
                if (const auto* v = Statistics::maxCapacityVehicle(dispatcher))
                    std::cout << "ID: " << v->getId() << "\n";
                break;
            case 21: {
                std::string name;
                clearInput();
                if (!std::getline(std::cin, name)) break;
                std::cout << "Average: " << Statistics::averageTimeOnRoute(dispatcher, name) << "\n";
                break;
            }
            case 22:
                dispatcher.generateActivityReport();
                break;
            case 23:
                std::cout << "Revenue: " << dispatcher.calculateTotalRevenue() << " RON\n";
                break;
            case 24: {
                std::string name;
                clearInput();
                if (!std::getline(std::cin, name)) break;
                Statistics::recommendOptimalVehicle(dispatcher, name);
                break;
            }
            case 25: {
                int id;
                std::string reason;
                if (!(std::cin >> id)) { clearInput(); break; }
                clearInput();
                if (!std::getline(std::cin, reason)) break;
                dispatcher.getMaintenance().sendToService(id, reason);
                break;
            }
            case 26: {
                int id;
                if (!(std::cin >> id)) { clearInput(); break; }
                dispatcher.getMaintenance().repairVehicle(id);
                break;
            }
            case 27:
                dispatcher.getMaintenance().generateTechnicalReport();
                break;
            case 28: {
                int ticketType;
                double price;
                if (!(std::cin >> ticketType >> price)) { clearInput(); break; }
                if (ticketType == 2) dispatcher.sellTicket(true, price, 0.5);
                else dispatcher.sellTicket(false, price);
                break;
            }
            default:
                break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            if (std::cin.eof()) break;
        }
    }
    return 0;
}
