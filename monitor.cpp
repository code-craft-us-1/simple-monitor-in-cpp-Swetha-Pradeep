#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <limits>
#include <list>
using std::cout , std::flush , std::this_thread::sleep_for , std::chrono::seconds;
std::list<std::pair<int , int>> tempratureLimits;
std::vector<std::string> tempratureMessages;
std::list<std::pair<float , float>> pulseRateLimits;
std::vector<std::string> pulseRateMessages;
std::list<std::pair<float , float>> spo2Limits;
std::vector<std::string> spo2Messages;
void sleep() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

void initializeTempratureLimits() {
    tempratureLimits.push_back(std::make_pair(std::numeric_limits<int>::min(), 95));
    tempratureMessages.push_back("Warning:HYPO_THERMIA");
    tempratureLimits.push_back(std::make_pair(95, 96.53));
    tempratureMessages.push_back("Warning:NEAR_HYPO");
    tempratureLimits.push_back(std::make_pair(96.54, 100.47));
    tempratureMessages.push_back("Normal Temprature");
    tempratureLimits.push_back(std::make_pair(100.48, 102));
    tempratureMessages.push_back("WARNING:NEAR_HYPER");
    tempratureLimits.push_back(std::make_pair(102, std::numeric_limits<int>::max()));
    tempratureMessages.push_back("HYPER_THERMIA");
}

void initializePulseRateLimits() {
    pulseRateLimits.push_back(std::make_pair(std::numeric_limits<float>::min(), 60));
    pulseRateMessages.push_back("WARNING:BRADYCHARDIA");
    pulseRateLimits.push_back(std::make_pair(60, 100));
    pulseRateMessages.push_back("NORMAL Pulse");
    pulseRateLimits.push_back(std::make_pair(100, std::numeric_limits<float>::max()));
    pulseRateMessages.push_back("WARNING:TACHYCHARDIA");
}

void initializeSPo2Limits() {
    spo2Limits.push_back(std::make_pair(std::numeric_limits<float>::min(), 80));
    spo2Messages.push_back("WARNING:HYPOXEMIA");
    spo2Limits.push_back(std::make_pair(80, std::numeric_limits<float>::max()));
    spo2Messages.push_back("Normal SPO2");
}

void writeTempratureMessage(std::string message) {
    std::cout << message << "\n";
}

void writePulseMessage(std::string message) {
    std::cout << message << "\n";
}

void writeSPo2Message(std::string message) {
    std::cout << message << "\n";
}

bool isTempraturNormal(int value) {
    int cnt = 0;
    for (auto i = tempratureLimits.begin(); i != tempratureLimits.end(); i++) {
        if (i->first == std::numeric_limits<int>::min() && value < i->second) {
            writeTempratureMessage(tempratureMessages[0]);
            break;
        } else if (i->second == std::numeric_limits<int>::max() && value > i->first) {
            writeTempratureMessage(tempratureMessages[4]);
            break;
        } else if ((value >= i->first) && (value <= i->second)) {
            writeTempratureMessage(tempratureMessages[cnt]);
            break;
        }
        cnt++;
    }

    if (tempratureMessages[cnt-1].find("Normal") != std::string::npos) {
        return true;
    }
    return false;
}

bool isPulseNormal(float value) {
    int cnt = 0;
    for (auto i = pulseRateLimits.begin(); i != pulseRateLimits.end(); i++) {
        if (i->first == std::numeric_limits<float>::min() && value < i->second) {
            writePulseMessage(pulseRateMessages[0]);
            break;
        } else if (i->second == std::numeric_limits<float>::max() && value > i->first) {
            writePulseMessage(pulseRateMessages[2]);
            break;
        } else if ((value >= i->first) && (value <= i->second)) {
            writePulseMessage(pulseRateMessages[cnt]);
            break;
        }
        cnt++;
    }
    if (pulseRateMessages[cnt-1].find("Normal") != std::string::npos) {
        return true;
    }
    return false;
}

bool isSpo2Normal(int value) {
    int cnt = 0;
    for (auto i = spo2Limits.begin(); i != spo2Limits.end(); i++) {
        if (i->first == std::numeric_limits<float>::min() && value < i->second) {
            writeSPo2Message(spo2Messages[0]);
            break;
        } else if (i->second == std::numeric_limits<float>::max() && value > i->first) {
            writeSPo2Message(spo2Messages[1]);
            break;
        } else if ((value >= i->first) && (value <= i->second)) {
            writeSPo2Message(spo2Messages[cnt]);
            break;
        }
        cnt++;
    }
    if (spo2Messages[cnt-1].find("Normal") != std::string::npos) {
        return true;
    }
    return false;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    initializeTempratureLimits();
    initializePulseRateLimits();
    initializeSPo2Limits();
    return isTempraturNormal(temperature) && isPulseNormal(pulseRate) && isSpo2Normal(spo2);
}
