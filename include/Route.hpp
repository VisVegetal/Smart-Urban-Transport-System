#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>

class Route {
private:
    std::string name;
    double distance;

public:
    Route() : distance(0.0) {}
    Route(std::string name, double distance);

    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] double getDistance() const { return distance; }
};

#endif
