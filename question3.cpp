#include <iostream>
#include <vector>
#include <chrono>
#include <random>

const int TOTAL_CHANNEL_BANDWIDTH = 20;  // Total bandwidth in MHz
const double TRANSMISSION_TIME = 5.0;    // Transmission time in ms
const int PACKET_SIZE = 1024;            // Packet size in bytes
const double MODULATION_RATE = 8.0;      // 256-QAM gives 8 bits per symbol
const double CODING_RATE = 5.0 / 6.0;    // Coding rate
const int ROUND_ROBIN_CYCLES = 1000;

class Packet {
public:
    int size;  // Packet size in bytes
    Packet(int s) : size(s) {}
};

class User {
public:
    User(int id) : id(id), dataTransmitted(0.0), latency(0.0), maxLatency(0.0) {}
    void addTransmission(double data, double time) {
        dataTransmitted += data;
        latency += time;
        if (time > maxLatency) maxLatency = time;
    }
    double getDataTransmitted() const { return dataTransmitted; }
    double getLatency() const { return latency; }
    double getMaxLatency() const { return maxLatency; }

private:
    int id;
    double dataTransmitted;
    double latency;
    double maxLatency;
};

class Channel {
public:
    Channel(int width) : bandwidth(width) {}

    int getBandwidth() const { return bandwidth; }

private:
    int bandwidth;  // Bandwidth in MHz
};

class AccessPoint {
public:
    AccessPoint(int numUsers, const std::vector<int>& subChannelWidths)
        : numUsers(numUsers), subChannelWidths(subChannelWidths) {
        for (int i = 0; i < numUsers; ++i) {
            users.push_back(User(i));
        }
        for (int width : subChannelWidths) {
            channels.push_back(Channel(width));
        }
    }

    void simulate() {
        for (Channel& channel : channels) {
            std::cout << "\nSimulating with " << channel.getBandwidth() << " MHz sub-channels:\n";
            resetMetrics();

            // Run simulation for specified cycles
            for (int cycle = 0; cycle < ROUND_ROBIN_CYCLES; ++cycle) {
                simulateCycle(channel);
            }

            // Calculate and display metrics
            double throughput = calculateThroughput();
            double avgLatency = calculateAverageLatency();
            double maxLatency = getMaxLatency();
            
            std::cout << "Throughput: " << throughput << " Mbps\n";
            std::cout << "Average Latency: " << avgLatency << " ms\n";
            std::cout << "Maximum Latency: " << maxLatency << " ms\n";
        }
    }

private:
    int numUsers;
    std::vector<int> subChannelWidths;
    std::vector<User> users;
    std::vector<Channel> channels;
    double totalDataTransmitted = 0.0;
    double totalLatency = 0.0;
    double maxLatency = 0.0;
    double totalTimeSpent = 0.0;

    void resetMetrics() {
        totalDataTransmitted = 0.0;
        totalLatency = 0.0;
        maxLatency = 0.0;
        totalTimeSpent = 0.0;
        for (auto& user : users) {
            user = User(user);
        }
    }

    void simulateCycle(Channel& channel) {
        // Distribute sub-channels among users
        int subChannels = TOTAL_CHANNEL_BANDWIDTH / channel.getBandwidth();
        
        for (int i = 0; i < numUsers; ++i) {
            User& user = users[i % numUsers];
            double userThroughput = calculateUserThroughput(channel.getBandwidth());
            double dataTransmitted = userThroughput * TRANSMISSION_TIME / 1e3;

            if (csma_ca()) { // If channel is free
                user.addTransmission(dataTransmitted, TRANSMISSION_TIME);
                totalDataTransmitted += dataTransmitted;
                totalLatency += TRANSMISSION_TIME;

                if (TRANSMISSION_TIME > maxLatency) {
                    maxLatency = TRANSMISSION_TIME;
                }
            }
        }
        
        totalTimeSpent += TRANSMISSION_TIME;
    }

    bool csma_ca() {
        // Simple CSMA/CA mechanism: Simulate a random chance of channel availability
        return rand() % 100 < 80; // 80% chance channel is available
    }

    double calculateUserThroughput(int bandwidth) {
        double symbolRate = bandwidth * 1e6;  // in symbols per second (MHz to Hz)
        double bitsPerSecond = symbolRate * MODULATION_RATE * CODING_RATE;  // bits per second
        double bytesPerSecond = bitsPerSecond / 8.0;
        return bytesPerSecond / 1e6;  // Convert to Mbps
    }

    double calculateThroughput() {
        return (totalDataTransmitted / totalTimeSpent) * 1e3; // Mbps
    }

    double calculateAverageLatency() {
        return totalLatency / numUsers; // ms
    }

    double getMaxLatency() {
        double maxLatency = 0.0;
        for (const auto& user : users) {
            if (user.getMaxLatency() > maxLatency) {
                maxLatency = user.getMaxLatency();
            }
        }
        return maxLatency;
    }
};

int main() {
    int numUsers = 10;
    std::vector<int> subChannelWidths = {2, 4, 10};  // Possible sub-channel bandwidths in MHz

    AccessPoint ap(numUsers, subChannelWidths);
    ap.simulate();

    return 0;
}
