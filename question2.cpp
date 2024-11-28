#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <numeric>
#include <algorithm>

const int MAX_BACKOFF_TIME = 10; // Maximum backoff time in milliseconds
const double BANDWIDTH = 20e6; // Bandwidth in Hz (20 MHz)
const int PACKET_SIZE = 1024; // Packet size in bytes
const double CODING_RATE = 5.0 / 6.0;
const int MODULATION_SCHEME_BITS = 8; // 256-QAM, 8 bits per symbol
const int BASELINE_DELAY = 5; // Baseline delay in milliseconds for transmission
const int CSI_PACKET_SIZE = 200; // CSI packet size in bytes
const int PARALLEL_TRANSMISSION_TIME_MS = 15; // 15 ms for parallel transmission

class Packet {
public:
    int packetID;
    int size;

    Packet(int id) : packetID(id), size(PACKET_SIZE) {}
    Packet(int id, int csiSize) : packetID(id), size(csiSize) {}  // For CSI packets
};

class Channel {
private:
    bool isFree;

public:
    Channel() : isFree(true) {}

    bool checkStatus() {
        return isFree;
    }

    void occupy() {
        isFree = false;
    }

    void release() {
        isFree = true;
    }
};

class User {
private:
    int userID;
    int backoffTime;
    Channel* channel;

public:
    User(int id, Channel* ch) : userID(id), backoffTime(0), channel(ch) {}

    bool senseChannel() {
        return channel->checkStatus();
    }

    void deferTransmission() {
        backoffTime = rand() % MAX_BACKOFF_TIME + 1;
    }

    int getUserID() const {
        return userID;
    }

    double calculateTransmissionTime() {
        double userThroughput = BANDWIDTH * MODULATION_SCHEME_BITS * CODING_RATE;
        double transmissionTime = (PACKET_SIZE * 8 * 1e3) / userThroughput; // in milliseconds
        return transmissionTime + BASELINE_DELAY; // add baseline delay
    }

    // Accept const reference to avoid non-const reference issue
    double transmitPacket(const Packet& packet, std::vector<double>& latencies) {
        using namespace std::chrono;
        auto startTime = high_resolution_clock::now();

        // Backoff mechanism
        while (!senseChannel()) {
            deferTransmission();
            std::this_thread::sleep_for(milliseconds(backoffTime));
        }

        channel->occupy();
        
        // Simulate packet transmission
        double transmissionTime = calculateTransmissionTime();
        std::this_thread::sleep_for(milliseconds(static_cast<int>(transmissionTime)));

        auto endTime = high_resolution_clock::now();
        double latency = duration_cast<milliseconds>(endTime - startTime).count();
        latencies.push_back(latency);

        channel->release();
        return latency;
    }

    void transmitCSI(std::vector<double>& latencies) {
        // Simulate the transmission of CSI (200-byte packet)
        Packet csiPacket(userID, CSI_PACKET_SIZE);
        transmitPacket(csiPacket, latencies);
    }
};

class AccessPoint {
public:
    std::vector<User> users;
    Channel channel;
    int totalPackets;

    AccessPoint(int userCount) : totalPackets(0) {
        for (int i = 0; i < userCount; i++) {
            users.emplace_back(i, &channel);
        }
    }
    void simulate(std::vector<double>& latencies) {
        // First, simulate the CSI exchange (sequential)
        for (User& user : users) {
            user.transmitCSI(latencies);
        }

        // Now, simulate parallel communication for 15 ms for all users
        auto startTime = std::chrono::high_resolution_clock::now();
        for (User& user : users) {
            // Passing temporary Packet object, which is now fine with const reference
            user.transmitPacket(Packet(user.getUserID()), latencies);
        }
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate total simulation time
        double simulationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        totalPackets = users.size(); // Each user transmits one packet

        // Repeat the process after each 15 ms slot (Parallel transmission)
        std::this_thread::sleep_for(std::chrono::milliseconds(PARALLEL_TRANSMISSION_TIME_MS));
    }

    double computeThroughput(double simulationTime) {
        double totalDataTransmitted = totalPackets * PACKET_SIZE * 8; // in bits
        return (totalDataTransmitted / simulationTime); // in Mbps
    }

    double computeAverageLatency(const std::vector<double>& latencies) {
        if (latencies.empty()) return 0;
        double sum = std::accumulate(latencies.begin(), latencies.end(), 0.0);
        return sum / latencies.size();
    }

    double computeMaxLatency(const std::vector<double>& latencies) {
        return latencies.empty() ? 0 : *std::max_element(latencies.begin(), latencies.end());
    }
};

void runSimulation(int userCount) {
    AccessPoint ap(userCount);
    std::vector<double> latencies;

    auto simStartTime = std::chrono::high_resolution_clock::now();
    ap.simulate(latencies);
    auto simEndTime = std::chrono::high_resolution_clock::now();
    double simulationTime = std::chrono::duration_cast<std::chrono::milliseconds>(simEndTime - simStartTime).count();

    double throughput = ap.computeThroughput(simulationTime);
    double avgLatency = ap.computeAverageLatency(latencies);
    double maxLatency = ap.computeMaxLatency(latencies);

    std::cout << "Results for " << userCount << " user(s):\n";
    std::cout << "Throughput: " << throughput << " Mbps\n";
    std::cout << "Average Latency: " << avgLatency << " ms\n";
    std::cout << "Maximum Latency: " << maxLatency << " ms\n\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    runSimulation(1);   // 1 user
    runSimulation(10);  // 10 users
    runSimulation(100); // 100 users

    return 0;
}
