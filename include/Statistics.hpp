#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <string>

class Dispatcher;
class Vehicle;

class Statistics {
public:
    static void vehicleDistribution(const Dispatcher& d);
    static double averageIncidentImpact(const Dispatcher& d);
    static void detailedReport(const Dispatcher& d);
    static const Vehicle* fastestVehicle(const Dispatcher& d, const std::string& routeName);
    static const Vehicle* maxCapacityVehicle(const Dispatcher& d);
    static double averageTimeOnRoute(const Dispatcher& d, const std::string& routeName);
    static void generalReport(const Dispatcher& d);
    static void recommendOptimalVehicle(const Dispatcher& d, const std::string& routeName);
};

#endif
