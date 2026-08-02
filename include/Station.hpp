#ifndef STATION_HPP
#define STATION_HPP

#include <string>
#include <vector>

class Station {
private:
    std::string name;                // name of the station
    std::vector<std::string> routes; // routes serving the station

public:
    explicit Station(const std::string& name);

    [[nodiscard]] const std::string& getName() const;
    void addRoute(const std::string& routeName);
    void show() const;
};

#endif
