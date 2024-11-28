# WiFi-5 Simulation with Multi-User MIMO

This project simulates the communication process of WiFi 5, utilizing the Multi-User MIMO (MU-MIMO) technique. It includes:
- Simulation of a round-robin scheduling process for users.
- Each user sequentially transmits Channel State Information (CSI).
- Parallel transmission of packets after CSI exchange.
- Throughput and latency calculation for different numbers of users.

## Project Description

WiFi 5 allows a new type of communication using Multi-User MIMO, where parallel transmission can occur after an initial CSI packet exchange. The simulation follows these steps:

1. **CSI Exchange**: Each user sequentially sends their Channel State Information (CSI), which is a 200-byte packet.
2. **Parallel Transmission**: Once CSI is exchanged, each user can transmit data in parallel for a duration of 15 ms.
3. **Round-Robin Scheduling**: Users transmit data packets one by one, deferring transmission if the channel is busy.

The simulation is designed to calculate the throughput, average latency, and maximum latency for various numbers of users (1, 10, 100).

## Prerequisites

To compile and run this project, you will need:

- A C++ compiler (e.g., GCC, Clang).
- A system supporting C++11 or later.

## Building the Program

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd WiFi5-Simulation

## Run the code
g++ -o wifi_simulation wifi5_simulation.cpp -std=c++11 -pthread

## Simulate 
./wifi5_simulation

## Code Structure

### 1. **`Packet` Class**
- **Purpose**: Represents a network packet, either a regular data packet or a CSI (Channel State Information) packet.
- **Constructor**:
  - `Packet(int id)` for creating a regular data packet with a default size (1024 bytes).
  - `Packet(int id, int csiSize)` for creating a CSI packet with a customizable size (200 bytes).
- **Attributes**:
  - `id`: Unique identifier for the packet.
  - `size`: Size of the packet in bytes.
- **Functions**:
  - `getSize()`: Returns the size of the packet.
  - `getId()`: Returns the ID of the packet.

### 2. **`Channel` Class**
- **Purpose**: Models a communication channel shared by multiple users.
- **Functions**:
  - `checkStatus()`: Checks if the channel is currently free (not occupied by any user).
  - `occupy()`: Occupies the channel for a specific user to transmit data.
  - `release()`: Releases the channel so that other users can use it.

### 3. **`User` Class**
- **Purpose**: Represents a user in the system, each connected to the access point.
- **Attributes**:
  - `userId`: Unique identifier for the user.
  - `transmissionTime`: Time taken to transmit a packet (in ms).
  - `latency`: Latency experienced by the user during transmission.
- **Functions**:
  - `senseChannel()`: Checks if the channel is free and available for transmission.
  - `deferTransmission()`: Simulates a backoff time before retrying transmission if the channel is busy.
  - `calculateTransmissionTime()`: Calculates the transmission time for the user's data packet based on the channel's bandwidth and delay.
  - `transmitPacket()`: Simulates the transmission of a data packet and records the latency.
  - `transmitCSI()`: Simulates the transmission of a CSI packet (200 bytes) for channel state information exchange.

### 4. **`AccessPoint` Class**
- **Purpose**: Manages the users and the shared channel. It coordinates packet transmission and calculates metrics like throughput and latency.
- **Attributes**:
  - `users`: List of `User` objects that are connected to the access point.
  - `channel`: An instance of the `Channel` class that is used for data transmission.
- **Functions**:
  - `simulate(std::vector<double>& latencies)`: Simulates the entire communication process, including CSI exchange and parallel packet transmission.
  - `computeThroughput(double simulationTime)`: Calculates the throughput of the system, which is the total data transmitted divided by the simulation time.
  - `computeAverageLatency(const std::vector<double>& latencies)`: Calculates the average latency across all users.
  - `computeMaxLatency(const std::vector<double>& latencies)`: Finds the maximum latency experienced by any user.

### 5. **`runSimulation` Function**
- **Purpose**: Runs the simulation for a given number of users and outputs the results.
- **Inputs**: The number of users to simulate (1, 10, 100).
- **Outputs**: Prints the throughput, average latency, and maximum latency for the specified number of users.

### 6. **Main Program Flow**
- **Purpose**: The entry point of the program that initiates the simulation process.
- **Steps**:
  - Initializes an `AccessPoint` object.
  - Creates a list of `User` objects.
  - Runs the simulation for different numbers of users.
  - Displays the results, including throughput, average latency, and maximum latency.

## File Structure

- `wifi_simulation.cpp`: Main C++ file containing the simulation logic and class definitions.
- `README.md`: This file, describing the project, usage, and code structure.
- `LICENSE`: License file for the project.

## Output
- Results for 1 user(s):
- Throughput: 167.184 Mbps
- Average Latency: 16.5 ms
- Maximum Latency: 20 ms

- Results for 10 user(s):
- Throughput: 249.756 Mbps
- Average Latency: 15.1 ms
- Maximum Latency: 21 ms

- Results for 100 user(s):
- Throughput: 259.816 Mbps
- Average Latency: 15.115 ms
- Maximum Latency: 29 ms
