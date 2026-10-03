# Smart Traffic Management System

## Overview
A C++ command-line prototype for managing traffic lanes, emergency vehicles, signal states and traffic reports.

## Features
- Vehicle registration and lane-based queue management
- FIFO processing with emergency priority selection
- Case-insensitive emergency vehicle detection
- Vehicle search using stored history
- Priority-based sorting with STL algorithms
- Traffic signal state management
- File-based traffic logging
- Traffic report generation
- Linux build and run scripts
- Modular C++ OOP design

## Concepts
- C++ classes, objects, constructors and encapsulation
- STL queue and vector
- Searching and sorting
- Lambda expressions
- File handling
- Input validation and exception-safe input recovery
- Linux command-line build/run workflow

## Build on Linux
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Vehicle.cpp TrafficSystem.cpp -o traffic_system
./traffic_system
```

Or use:
```bash
./build.sh
./run.sh
```

## Suggested Git structure
Use a main branch for stable code and feature branches for individual modules.

## Project scope
This is a software prototype/simulation. Real sensors, cameras, GPS and physical traffic lights are future extensions.

## Linux Character Device Driver

The project includes a Linux character device driver for traffic signal state management.

Driver files:
- `driver/traffic_signal_driver.c`
- `driver/Makefile`
- `driver/traffic_signal_driver.ko`

The driver uses character-device concepts such as:
- Device registration
- `open`, `read`, `write` and `release` operations
- `copy_from_user()`
- Kernel logging using `printk()`
- Kernel module loading using `insmod`

Supported traffic signal states:
- RED
- GREEN
- YELLOW

## QEMU Testing

QEMU is used to provide a Linux environment for testing the kernel module.

The Linux kernel image, initramfs and traffic signal driver module are used to boot a minimal Linux environment and test the driver.

The QEMU workflow is based on the Linux kernel-module and driver-development concepts covered in the training material.

