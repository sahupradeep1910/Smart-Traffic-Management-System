# Smart Traffic Management System

## Overview

The **Smart Traffic Management System** is a Linux-based traffic management application developed using **C++**.

The system provides a simple way to manage vehicles, traffic queues, priority vehicles, traffic signal states, traffic records and traffic reports.

The project also incorporates a **Linux Character Device Driver** implemented as a kernel module for traffic signal management. The driver is compiled as a `.ko` kernel object and is intended to be tested in a Linux environment using **QEMU**.

---

## Objectives

- Manage vehicle information efficiently.
- Maintain and process traffic queues.
- Identify and handle priority vehicles.
- Manage traffic signal states.
- Maintain traffic activity logs.
- Generate traffic reports.
- Apply object-oriented programming concepts using C++.
- Implement a Linux Character Device Driver.
- Understand interaction between user-space applications and kernel-space driver code.
- Use QEMU for Linux driver testing.

---

## Features

### Vehicle Management
- Add vehicle details.
- Display registered vehicles.
- Search for vehicles.

### Traffic Queue Management
- Add and process vehicles in the traffic queue.
- Display traffic-related information.

### Priority Vehicle Handling
- Identify priority/emergency vehicles.
- Process priority vehicles separately.

### Traffic Signal Management

The system supports three traffic signal states:

- RED
- GREEN
- YELLOW

### Traffic Logging

Traffic-related activities are stored in:

```text
data/traffic_log.txt
```

### Traffic Reports

The application provides traffic information through a report option.

---

## System Architecture

```text
                    Smart Traffic Management System
                                  |
                                  v
                       C++ Traffic Application
                                  |
              +-------------------+-------------------+
              |                   |                   |
              v                   v                   v
       Vehicle Management   Traffic Queue      Signal Management
              |                   |                   |
              +-------------------+-------------------+
                                  |
                                  v
                         Traffic Information
                                  |
                                  v
                    Linux Character Device Driver
                                  |
                                  v
                       Traffic Signal Interface
```

---

## Project Workflow

```text
Start
  |
  v
Main Menu
  |
  +-- Add Vehicle
  |
  +-- Display Vehicles
  |
  +-- Process Traffic Queue
  |
  +-- Traffic Status
  |
  +-- Search Vehicle
  |
  +-- Priority Vehicles
  |
  +-- Priority Sorting
  |
  +-- Change Signal State
  |
  +-- Traffic Report
  |
  +-- Traffic Log
  |
  +-- Exit
  |
  v
End
```

---

## Technologies Used

- **Programming Language:** C++
- **Driver Language:** C
- **Operating System:** Linux
- **Kernel Module:** Linux Character Device Driver
- **Driver Format:** `.ko` Kernel Object
- **Virtual Testing Environment:** QEMU
- **Compiler:** G++
- **Build System:** Linux Kernel Build System

---

## C++ Application

The main traffic management application is developed using C++.

The application is organized into separate classes and source files.

### Main Components

```text
main.cpp
    |
    +-- Controls the application menu and user interaction

Vehicle.h / Vehicle.cpp
    |
    +-- Handles vehicle-related information

TrafficSystem.h / TrafficSystem.cpp
    |
    +-- Handles traffic management operations
```

The application uses object-oriented programming concepts to organize vehicle and traffic management functionality.

---

## Linux Character Device Driver

The project includes a Linux Character Device Driver for traffic signal management.

### Driver Files

```text
driver/
+-- traffic_signal_driver.c
+-- traffic_signal_driver.ko
+-- Makefile
```

The driver is implemented as a Linux kernel module.

### Character Device Concepts Used

The driver incorporates the following concepts:

- Character device registration
- Device number allocation
- File operations
- `open()`
- `read()`
- `write()`
- `release()`
- `copy_from_user()`
- Kernel logging using `printk()`
- Kernel module loading using `insmod`

A character device provides a file-like interface for interaction between user space and the driver.

### Supported Signal States

```text
RED
GREEN
YELLOW
```

The driver maintains the traffic signal state and handles valid signal-state input.

---

## Kernel Module

The traffic signal driver is compiled as a Linux kernel object:

```text
traffic_signal_driver.ko
```

Kernel modules can be loaded into the running Linux kernel using:

```bash
insmod traffic_signal_driver.ko
```

The module can be removed using:

```bash
rmmod traffic_signal_driver
```

Kernel messages generated using `printk()` can be viewed through the Linux kernel log.

---

## QEMU Testing

**QEMU** is used as a virtual Linux environment for testing the kernel module and driver.

The QEMU setup uses:

```text
Linux Kernel
     |
     v
Initramfs
     |
     v
Traffic Signal Driver
     |
     v
Minimal Linux Environment
```

The driver module is included in the QEMU initramfs and loaded during the Linux boot process.

QEMU provides a safe environment for testing Linux kernel modules and drivers without requiring dedicated physical hardware.

> Note: The current implementation includes the QEMU-based driver loading setup. Physical traffic-signal hardware is not connected, and runtime `/dev/traffic_signal` interaction was not verified in the final test environment.

---

## Project Structure

```text
Smart Traffic Management System/
|
+-- main.cpp
|
+-- Vehicle.h
+-- Vehicle.cpp
|
+-- TrafficSystem.h
+-- TrafficSystem.cpp
|
+-- data/
|   +-- traffic_log.txt
|
+-- driver/
|   +-- traffic_signal_driver.c
|   +-- traffic_signal_driver.ko
|   +-- Makefile
|
+-- build.sh
+-- run.sh
+-- traffic_system
+-- README.md
```

---

## Build and Run on Linux

Navigate to the project directory:

```bash
cd "Smart Traffic Management System"
```

Compile the C++ application:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
main.cpp Vehicle.cpp TrafficSystem.cpp \
-o traffic_system
```

Run the application:

```bash
./traffic_system
```

The same commands are also provided through the project's `build.sh` and `run.sh` scripts.

---

## Driver Build

The driver is built using the Linux kernel build system and matching Linux kernel headers.

Navigate to the driver directory:

```bash
cd driver
```

Build the kernel module with:

```bash
make
```

The resulting kernel module is:

```text
traffic_signal_driver.ko
```

To clean generated kernel-module build files:

```bash
make clean
```

---

## Training Concepts Used

The project applies concepts covered during Linux and system training.

### Linux Kernel Modules

The traffic signal driver is implemented as a Linux kernel module.

### Character Device Driver

The driver follows the character-device approach and provides file operations such as:

```text
open
read
write
release
```

### Kernel Logging

The driver uses:

```c
printk()
```

for kernel-level logging.

### User and Kernel Space Data Transfer

The driver uses:

```c
copy_from_user()
```

to safely receive data from user space.

### QEMU

QEMU is used to provide a virtual Linux environment for kernel-module and driver testing.

---

## Limitations

- The system is currently a software-based traffic management application.
- No physical traffic signal hardware is connected.
- The Linux driver is designed for traffic signal state management and testing.
- QEMU is used as the virtual testing environment.
- The current project does not include a network communication layer.

---

## Conclusion

The **Smart Traffic Management System** combines a C++ traffic management application with Linux kernel and character-device driver concepts.

The project demonstrates vehicle management, traffic queue processing, priority vehicle handling, traffic signal management, traffic logging and traffic reporting.

The Linux Character Device Driver and QEMU-based testing provide practical application of the Linux Kernel Modules and Driver Development concepts covered during the training.
