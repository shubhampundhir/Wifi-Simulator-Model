# WiFi4 Communication Simulator and Modelling

## Project Overview

This project simulates WiFi communication using object-oriented principles such as inheritance, data abstraction, data hiding, and polymorphism. The simulation involves users communicating through a single access point (AP) where packets are transmitted based on a simple backoff mechanism when the channel is busy.

### Key Features
- **User and Access Point Simulation:** Multiple users (1, 10, and 100) communicate with a single access point.
- **Backoff Mechanism:** Users defer their packet transmission if the channel is busy, and retransmit after a random backoff time.
- **Throughput and Latency Computation:** The simulation computes throughput, average latency, and maximum latency during communication.
- **Channel Access:** The channel is either free or occupied, and only one user can transmit at a time.

### Assumptions
- 20 MHz of bandwidth is used.
- 256-QAM modulation with a 5/6 coding rate is used for packet transmission.
- Each packet is 1 KB in size.
- Other transmission delays such as DIFS, CIFS, and guard intervals are ignored.

## Classes and Description

### 1. `Packet`
Represents a data packet. Each packet has:
- **packetID**: A unique identifier for each packet.
- **size**: The size of the packet (1 KB).

### 2. `Channel`
Represents the communication channel between the users and the access point. The channel can be:
- **free**: Available for transmission.
- **occupied**: Busy with a transmission.

The `Channel` class provides:
- **checkStatus()**: Returns whether the channel is free or occupied.
- **occupy()**: Marks the channel as occupied.
- **release()**: Frees the channel.

### 3. `User`
Represents a user who is attempting to transmit a packet. Each user has:
- **userID**: A unique identifier for the user.
- **backoffTime**: The time the user needs to wait before retransmitting if the channel is busy.

The `User` class provides:
- **senseChannel()**: Checks if the channel is free.
- **deferTransmission()**: Defers transmission by a random backoff time.
- **calculateTransmissionTime()**: Calculates the time required to transmit a packet.
- **transmitPacket()**: Simulates the packet transmission process, including backoff and actual transmission.

### 4. `AccessPoint`
Represents the access point that manages the channel and all users. The `AccessPoint` class includes:
- **users**: A list of users attempting to transmit data.
- **channel**: The shared communication channel.
- **totalPackets**: The total number of packets transmitted during the simulation.

The `AccessPoint` class provides:
- **simulate()**: Simulates packet transmission for all users.
- **computeThroughput()**: Computes the throughput of the system in Mbps.
- **computeAverageLatency()**: Computes the average latency for all users.
- **computeMaxLatency()**: Computes the maximum latency for all users.

### 5. `runSimulation()`
This function runs the simulation for a given number of users, simulates packet transmission, and calculates throughput, average latency, and maximum latency.

## Simulation Scenarios

The simulation runs for three different user configurations:
- **1 user**: A single user communicates with the access point.
- **10 users**: Ten users communicate with the access point.
- **100 users**: One hundred users communicate with the access point.

For each configuration, the results (throughput, average latency, and maximum latency) are printed.

### Output Format
Results for 1 user(s):  
Throughput: 910.222 Mbps
Average Latency: 9 ms   
Maximum Latency: 9 ms   

Results for 10 user(s): 
Throughput: 531.948 Mbps
Average Latency: 15 ms  
Maximum Latency: 17 ms  

Results for 100 user(s): 
Throughput: 525.465 Mbps 
Average Latency: 15.09 ms
Maximum Latency: 23 ms 
