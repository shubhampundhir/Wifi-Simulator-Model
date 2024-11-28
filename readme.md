# WiFi Communication Simulation and Modelling

## Project Overview

This project is a simulation of WiFi communication using various standards (WiFi 4, WiFi 5, and WiFi 6). The goal of the project is to model how data is transmitted over different WiFi communication systems, simulate throughput, latency, and evaluate the behavior of multiple users in each communication standard.

The project is designed using object-oriented principles such as inheritance, polymorphism, encapsulation, and data abstraction. The WiFi communication protocols modeled are as follows:

1. **WiFi 4 Communication**: Uses the CSMA/CA protocol where the channel is sniffed before transmission.
2. **WiFi 5 Simulation**: Introduces multi-user MIMO and parallel communication after an initial synchronization phase.
3. **WiFi 6 Simulation**: Uses OFDMA with dynamic sub-channel allocation for parallel communication.

## Project Requirements

### WiFi 4 Simulation
- Simulates a simple communication scenario where:
  - **1 user and 1 AP**
  - **10 users and 1 AP**
  - **100 users and 1 AP**
  
  The transmission happens using a single 20 MHz bandwidth. The modulation used is **256-QAM**, and the coding rate is **5/6**. Each packet has a size of **1 KB**. The transmission is based on CSMA/CA where the channel is sniffed and if it’s free, data is transmitted. If the channel is occupied, a backoff time is applied.

### WiFi 5 Simulation
- Simulates communication using **multi-user MIMO**.
- Parallel communication happens after an initial broadcast packet, where each user sends channel state information.
- The process is repeated for **15 ms**.

### WiFi 6 Simulation
- Simulates communication using **OFDMA**.
- A **20 MHz** channel is subdivided into 2 MHz, 4 MHz, or 10 MHz sub-channels, which can be used in parallel for 5 ms.
- After 5 ms, the channel allocation is refreshed.

### Key Metrics
- **Throughput**: Measures the amount of data transmitted in Mbps.
- **Average Latency**: Measures the average delay experienced by users.
- **Maximum Latency**: Measures the maximum delay experienced by any user.


## Key Classes

### Packet Class
- Represents a data packet being transmitted.
- Contains attributes like `size` (in bytes) to track packet size.

### User Class
- Represents a user in the network.
- Tracks metrics such as data transmitted, latency, and maximum latency experienced by the user.

### Channel Class
- Represents the communication channel.
- Includes attributes like bandwidth and supports sub-channel allocation.

### AccessPoint Class
- Represents the Access Point in the WiFi network.
- Handles simulation of user communication through round-robin scheduling and different WiFi communication standards.

### Simulation Class
- Responsible for running the simulation.
- Manages the scheduling of users and the calculation of throughput, latency, and other metrics.

## How to Run the Simulation

### Prerequisites
To build and run this project, you need a C++ compiler (such as g++ or clang++) and a suitable build environment (such as Make or CMake).

### Compilation

1. Clone the repository to your local machine.
2. Navigate to the project directory.

For Linux/macOS, you can use:

```bash
g++ -o wifi_simulation main.cpp src/*.cpp -std=c++11
