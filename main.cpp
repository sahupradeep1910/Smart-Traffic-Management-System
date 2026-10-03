#include <iostream>
#include <limits>
#include "TrafficSystem.h"

using namespace std;

int main() {
    TrafficSystem system;
    int choice;

    do {
        cout << "\n============================================\n";
        cout << "      SMART TRAFFIC MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Add Vehicle\n";
        cout << "2. Display Waiting Vehicles\n";
        cout << "3. Process Next Vehicle\n";
        cout << "4. Show Traffic Status\n";
        cout << "5. Save Traffic Log\n";
        cout << "6. Search Vehicle\n";
        cout << "7. Show Emergency Vehicles\n";
        cout << "8. Sort Vehicles by Priority\n";
        cout << "9. Change Traffic Signal\n";
        cout << "10. Generate Traffic Report\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: system.addVehicle(); break;
            case 2: system.displayVehicles(); break;
            case 3: system.processNextVehicle(); break;
            case 4: system.showTrafficStatus(); break;
            case 5: system.saveTrafficLog(); break;
            case 6: system.searchVehicle(); break;
            case 7: system.showPriorityVehicles(); break;
            case 8: system.sortVehiclesByPriority(); break;
            case 9: system.changeSignalState(); break;
            case 10: system.generateTrafficReport(); break;
            case 11:
                cout << "\nExiting Smart Traffic Management System...\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}
