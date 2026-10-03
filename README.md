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

