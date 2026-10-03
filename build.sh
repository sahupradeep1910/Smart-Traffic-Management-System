#!/usr/bin/env bash
set -e
mkdir -p data
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Vehicle.cpp TrafficSystem.cpp -o traffic_system
printf '\nBuild successful. Run with: ./traffic_system\n'
