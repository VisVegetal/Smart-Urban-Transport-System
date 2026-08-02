#ifndef MAINTENANCE_HPP
#define MAINTENANCE_HPP

#include <map>
#include <string>
#include <vector>

enum class VehicleState { OPERATIONAL, SERVICE_DUE, IN_SERVICE, RETIRED };

class Maintenance {
private:
    std::map<int, VehicleState> fleetStatus;
    std::map<int, int> kilometersDriven;
    std::map<int, std::vector<std::string>> serviceHistory;
    static constexpr int MAINTENANCE_THRESHOLD = 5000;

public:
    Maintenance() = default;
    Maintenance(const Maintenance& other) = default;
    Maintenance& operator=(const Maintenance& other) = default;
    ~Maintenance() = default;

    void updateMileage(int id, int km);
    void sendToService(int id, const std::string& reason);
    void repairVehicle(int id);

    [[nodiscard]] bool canRun(int id) const;
    [[nodiscard]] std::string getStatusDetails(int id) const;

    void generateTechnicalReport() const;
};

#endif
