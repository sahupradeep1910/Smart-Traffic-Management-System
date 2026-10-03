#include "Vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle()
    : vehicleNumber(""), vehicleType(""), laneNumber(0), priority(1) {}

Vehicle::Vehicle(const string& number, const string& type, int lane, int p)
    : vehicleNumber(number), vehicleType(type), laneNumber(lane), priority(p) {}

string Vehicle::getVehicleNumber() const {
    return vehicleNumber;
}

string Vehicle::getVehicleType() const {
    return vehicleType;
}

int Vehicle::getLaneNumber() const {
    return laneNumber;
}

int Vehicle::getPriority() const {
    return priority;
}

void Vehicle::display() const {
    cout << "Vehicle No. : " << vehicleNumber << '\n';
    cout << "Type        : " << vehicleType << '\n';
    cout << "Lane        : " << laneNumber << '\n';
    cout << "Priority    : " << priority;
    if (priority > 1) cout << " (EMERGENCY)";
    cout << '\n';
}
