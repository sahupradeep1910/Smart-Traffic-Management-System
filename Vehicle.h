#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    std::string vehicleNumber;
    std::string vehicleType;
    int laneNumber;
    int priority;

public:
    Vehicle();
    Vehicle(const std::string& number, const std::string& type, int lane, int priority = 1);

    std::string getVehicleNumber() const;
    std::string getVehicleType() const;
    int getLaneNumber() const;
    int getPriority() const;

    void display() const;
};

#endif
