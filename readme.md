# WiFi 6 Communication Simulation with OFDMA

This project simulates the communication process using WiFi 6 with OFDMA (Orthogonal Frequency Division Multiple Access) and round-robin scheduling. The simulation runs multiple users on a channel that is subdivided into 2 MHz, 4 MHz, and 10 MHz sub-channels. The goal is to calculate throughput, average latency, and maximum latency for each case.

## Features
- **OFDMA-based communication** using different sub-channel bandwidths (2 MHz, 4 MHz, and 10 MHz).
- **Round-robin scheduling** to distribute transmission opportunities among users.
- **CSMA/CA** (Carrier Sense Multiple Access with Collision Avoidance) to model channel availability.
- **Transmission time of 5ms** with a packet size of 1024 bytes and a 256-QAM modulation rate.

## Code Structure

### 1. **`Packet` Class**
- **Purpose**: Represents a network packet.
- **Attributes**:
  - `size`: Size of the packet in bytes.
- **Constructor**:
  - `Packet(int s)`: Initializes a packet with the given size.
  
### 2. **`User` Class**
- **Purpose**: Represents a user in the WiFi 6 system.
- **Attributes**:
  - `id`: Unique identifier for the user.
  - `dataTransmitted`: Total data transmitted by the user (in bytes).
  - `latency`: Total latency experienced by the user (in ms).
  - `maxLatency`: Maximum latency experienced by the user during transmissions (in ms).
- **Methods**:
  - `addTransmission(double data, double time)`: Adds data transmission and latency information for the user.
  - `getDataTransmitted()`: Returns the total data transmitted by the user.
  - `getLatency()`: Returns the total latency experienced by the user.
  - `getMaxLatency()`: Returns the maximum latency for the user.

### 3. **`Channel` Class**
- **Purpose**: Represents the communication channel, which can be divided into sub-channels of varying bandwidth.
- **Attributes**:
  - `bandwidth`: The bandwidth of the channel in MHz.
- **Methods**:
  - `getBandwidth()`: Returns the bandwidth of the channel.

### 4. **`AccessPoint` Class**
- **Purpose**: Represents the access point managing multiple users and channels.
- **Attributes**:
  - `numUsers`: Number of users connected to the access point.
  - `subChannelWidths`: List of sub-channel widths (2 MHz, 4 MHz, 10 MHz).
  - `users`: List of users connected to the access point.
  - `channels`: List of channels with different bandwidths.
  - `totalDataTransmitted`: Total data transmitted across all users (in bytes).
  - `totalLatency`: Total latency accumulated for all users (in ms).
  - `maxLatency`: Maximum latency encountered by any user.
  - `totalTimeSpent`: Total time spent on the simulation (in ms).
- **Methods**:
  - `simulate()`: Runs the simulation for all sub-channel widths (2 MHz, 4 MHz, and 10 MHz).
  - `resetMetrics()`: Resets the metrics (data transmitted, latency, etc.) for each simulation cycle.
  - `simulateCycle(Channel& channel)`: Simulates a cycle of transmission for each user over the given channel.
  - `csma_ca()`: Simulates a simple CSMA/CA mechanism, providing an 80% chance that the channel is available for transmission.
  - `calculateUserThroughput(int bandwidth)`: Calculates the throughput for each user based on the channel bandwidth.
  - `calculateThroughput()`: Calculates the overall throughput of the system.
  - `calculateAverageLatency()`: Calculates the average latency across all users.
  - `getMaxLatency()`: Gets the maximum latency across all users.

### 5. **`main()` Function**
- **Purpose**: The entry point of the simulation program.
- **Steps**:
  - Initializes an `AccessPoint` object with a specified number of users and sub-channel widths.
  - Runs the simulation for all sub-channel widths (2 MHz, 4 MHz, and 10 MHz).
  - Displays throughput, average latency, and maximum latency for each case.

## File Structure

- **`wifi_simulation.cpp`**: Main C++ file containing the simulation logic and class definitions.
- **`README.md`**: This file, describing the project, usage, and code structure.
- **`LICENSE`**: License file for the project.

## Compilation and Execution

To compile and run the simulation, follow these steps:

### 1. **Compiling**
- Open a terminal and navigate to the directory containing `wifi_simulation.cpp`.
- Compile the code using a C++ compiler like g++:
  ```bash
  g++ wifi_simulation.cpp -o wifi_simulation
