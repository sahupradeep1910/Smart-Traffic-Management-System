#ifndef TRAFFIC_SYSTEM_H
#define TRAFFIC_SYSTEM_H

#include <queue>
#include <string>
#include <vector>
#include "Vehicle.h"

enum class SignalState {
    RED,
    GREEN,
    YELLOW
};

class TrafficSystem {
private:
    std::queue<Vehicle> laneQueues[3];
    std::vector<Vehicle> allVehicles;
    std::string trafficLogFile;
    SignalState signalState;

    int calculatePriority(const std::string& type) const;
    bool isEmergency(const Vehicle& vehicle) const;
    std::string signalStateToString() const;
    void writeLog(const std::string& message) const;

public:
    TrafficSystem();

    void addVehicle();
    void displayVehicles() const;
    void processNextVehicle();
    void showTrafficStatus() const;
    void saveTrafficLog() const;
    void searchVehicle() const;
    void showPriorityVehicles() const;
    void sortVehiclesByPriority() const;
    void changeSignalState();
    void generateTrafficReport() const;
};

#endif
