#include "TrafficSystem.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

TrafficSystem::TrafficSystem()
    : trafficLogFile("data/traffic_log.txt"), signalState(SignalState::RED) {}

int TrafficSystem::calculatePriority(const string& type) const {
    string normalized = type;
    transform(normalized.begin(), normalized.end(), normalized.begin(),
              [](unsigned char ch) { return static_cast<char>(tolower(ch)); });

    if (normalized == "ambulance" || normalized == "firetruck" ||
        normalized == "fire truck" || normalized == "police") {
        return 10;
    }
    return 1;
}

bool TrafficSystem::isEmergency(const Vehicle& vehicle) const {
    return vehicle.getPriority() > 1;
}

string TrafficSystem::signalStateToString() const {
    switch (signalState) {
        case SignalState::RED: return "RED";
        case SignalState::GREEN: return "GREEN";
        case SignalState::YELLOW: return "YELLOW";
    }
    return "UNKNOWN";
}

void TrafficSystem::writeLog(const string& message) const {
    ofstream logFile(trafficLogFile, ios::app);
    if (logFile.is_open()) {
        logFile << message << '\n';
    }
}

void TrafficSystem::addVehicle() {
    string number, type;
    int lane;

    cout << "\nEnter vehicle number: ";
    cin >> number;

    cout << "Enter vehicle type (Car/Bus/Bike/Truck/Ambulance/FireTruck/Police): ";
    cin >> type;

    cout << "Enter lane number (1-3): ";
    if (!(cin >> lane)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid lane input.\n";
        return;
    }

    if (lane < 1 || lane > 3) {
        cout << "Invalid lane number. Please choose 1, 2 or 3.\n";
        return;
    }

    int priority = calculatePriority(type);
    Vehicle vehicle(number, type, lane, priority);
    laneQueues[lane - 1].push(vehicle);
    allVehicles.push_back(vehicle);

    cout << "Vehicle added successfully to Lane " << lane << ".\n";

    if (isEmergency(vehicle)) {
        cout << "!!! EMERGENCY VEHICLE DETECTED - PRIORITY 10 !!!\n";
        writeLog("Emergency vehicle added | " + number + " | " + type + " | Lane " + to_string(lane));
    } else {
        writeLog("Vehicle added | " + number + " | " + type + " | Lane " + to_string(lane));
    }
}

void TrafficSystem::displayVehicles() const {
    cout << "\n========== WAITING VEHICLES ==========\n";
    bool found = false;

    for (int i = 0; i < 3; ++i) {
        cout << "\nLane " << i + 1 << " (" << laneQueues[i].size() << " vehicles)\n";
        if (laneQueues[i].empty()) {
            cout << "  No vehicles waiting.\n";
            continue;
        }

        queue<Vehicle> temp = laneQueues[i];
        while (!temp.empty()) {
            const Vehicle& vehicle = temp.front();
            cout << "  - " << vehicle.getVehicleNumber()
                 << " | " << vehicle.getVehicleType()
                 << " | Priority " << vehicle.getPriority() << '\n';
            temp.pop();
            found = true;
        }
    }

    if (!found) cout << "\nNo vehicles are currently waiting.\n";
}

void TrafficSystem::processNextVehicle() {
    int lane;
    cout << "\nEnter lane to process (1-3): ";
    if (!(cin >> lane)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid lane input.\n";
        return;
    }

    if (lane < 1 || lane > 3) {
        cout << "Invalid lane number.\n";
        return;
    }
    if (laneQueues[lane - 1].empty()) {
        cout << "Lane " << lane << " has no waiting vehicles.\n";
        return;
    }

    // Select the highest-priority vehicle while preserving FIFO order among ties.
    queue<Vehicle> temp = laneQueues[lane - 1];
    Vehicle selected;
    bool found = false;
    int bestPriority = -1;

    while (!temp.empty()) {
        Vehicle current = temp.front();
        temp.pop();
        if (!found || current.getPriority() > bestPriority) {
            selected = current;
            bestPriority = current.getPriority();
            found = true;
        }
    }

    queue<Vehicle> rebuilt;
    bool removed = false;
    while (!laneQueues[lane - 1].empty()) {
        Vehicle current = laneQueues[lane - 1].front();
        laneQueues[lane - 1].pop();
        if (!removed && current.getVehicleNumber() == selected.getVehicleNumber()) {
            removed = true;
        } else {
            rebuilt.push(current);
        }
    }
    laneQueues[lane - 1] = rebuilt;

    cout << "\nVehicle processed successfully:\n";
    selected.display();
    writeLog("Processed | " + selected.getVehicleNumber() + " | " + selected.getVehicleType() +
             " | Lane " + to_string(selected.getLaneNumber()) + " | Priority " + to_string(selected.getPriority()));
}

void TrafficSystem::showTrafficStatus() const {
    cout << "\n========== TRAFFIC STATUS ==========\n";
    int total = 0;
    for (int i = 0; i < 3; ++i) {
        int count = static_cast<int>(laneQueues[i].size());
        total += count;
        cout << "Lane " << i + 1 << " : " << count << " vehicles\n";
    }
    cout << "Signal State         : " << signalStateToString() << '\n';
    cout << "Total waiting vehicles: " << total << '\n';
}

void TrafficSystem::saveTrafficLog() const {
    ofstream logFile(trafficLogFile, ios::app);
    if (!logFile.is_open()) {
        cout << "Unable to open traffic log file.\n";
        return;
    }

    int total = 0;
    logFile << "\n--- Traffic Status Snapshot ---\n";
    for (int i = 0; i < 3; ++i) {
        int count = static_cast<int>(laneQueues[i].size());
        total += count;
        logFile << "Lane " << i + 1 << " : " << count << " vehicles\n";
    }
    logFile << "Signal State: " << signalStateToString() << '\n';
    logFile << "Total waiting vehicles: " << total << "\n";
    logFile << "-------------------------------\n";

    cout << "Traffic status saved to " << trafficLogFile << ".\n";
}

void TrafficSystem::searchVehicle() const {
    string number;
    cout << "\nEnter vehicle number to search: ";
    cin >> number;

    for (const Vehicle& vehicle : allVehicles) {
        if (vehicle.getVehicleNumber() == number) {
            cout << "\nVehicle found:\n";
            vehicle.display();
            return;
        }
    }
    cout << "Vehicle not found in system history.\n";
}

void TrafficSystem::showPriorityVehicles() const {
    cout << "\n========== EMERGENCY VEHICLES ==========\n";
    bool found = false;
    for (const Vehicle& vehicle : allVehicles) {
        if (isEmergency(vehicle)) {
            vehicle.display();
            cout << "----------------------------------------\n";
            found = true;
        }
    }
    if (!found) cout << "No emergency vehicles registered.\n";
}

void TrafficSystem::sortVehiclesByPriority() const {
    if (allVehicles.empty()) {
        cout << "\nNo vehicles available for sorting.\n";
        return;
    }

    vector<Vehicle> sortedVehicles = allVehicles;
    sort(sortedVehicles.begin(), sortedVehicles.end(),
         [](const Vehicle& a, const Vehicle& b) {
             return a.getPriority() > b.getPriority();
         });

    cout << "\n====== VEHICLES SORTED BY PRIORITY ======\n";
    for (const Vehicle& vehicle : sortedVehicles) {
        cout << vehicle.getVehicleNumber() << " | "
             << vehicle.getVehicleType() << " | Priority "
             << vehicle.getPriority() << '\n';
    }
}

void TrafficSystem::changeSignalState() {
    cout << "\nCurrent Signal: " << signalStateToString() << '\n';
    cout << "1. RED\n2. GREEN\n3. YELLOW\nChoose new state: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid signal choice.\n";
        return;
    }

    switch (choice) {
        case 1: signalState = SignalState::RED; break;
        case 2: signalState = SignalState::GREEN; break;
        case 3: signalState = SignalState::YELLOW; break;
        default:
            cout << "Invalid signal choice.\n";
            return;
    }

    cout << "Signal changed to " << signalStateToString() << ".\n";
    writeLog("Signal changed to " + signalStateToString());
}

void TrafficSystem::generateTrafficReport() const {
    int total = 0;
    int emergency = 0;
    int busiestLane = 1;
    size_t busiestCount = 0;

    for (int i = 0; i < 3; ++i) {
        size_t count = laneQueues[i].size();
        total += static_cast<int>(count);
        if (count > busiestCount) {
            busiestCount = count;
            busiestLane = i + 1;
        }
    }

    for (const Vehicle& vehicle : allVehicles) {
        if (isEmergency(vehicle)) ++emergency;
    }

    cout << "\n============= TRAFFIC REPORT =============\n";
    cout << "Total registered vehicles : " << allVehicles.size() << '\n';
    cout << "Currently waiting        : " << total << '\n';
    cout << "Emergency vehicles       : " << emergency << '\n';
    cout << "Busiest waiting lane     : Lane " << busiestLane << " (" << busiestCount << ")\n";
    cout << "Current signal state     : " << signalStateToString() << '\n';
    cout << "===========================================\n";
}
