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

enum ParameterType {
    TEMPERATURE,
    PULSE_RATE,
    SPO2
};

void sleep() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

template <typename T>
void initializeLimits(std::list<std::pair<T, T>>& limits, std::vector<std::string>& messages, const std::vector<std::pair<T, T>>& limitPairs, const std::vector<std::string>& limitMessages) {
    for (size_t i = 0; i < limitPairs.size(); ++i) {
        limits.push_back(limitPairs[i]);
        messages.push_back(limitMessages[i]);
    }
}
void initializeTempratureLimits() {
    std::vector<std::pair<int, int>> tempLimits = {
        {std::numeric_limits<int>::min(), 95},
        {95, 96.53},
        {96.54, 100.47},
        {100.48, 102},
        {102, std::numeric_limits<int>::max()}
    };
    std::vector<std::string> tempMessages = {
        "Warning:HYPO_THERMIA",
        "Warning:NEAR_HYPO",
        "Normal Temprature",
        "WARNING:NEAR_HYPER",
        "HYPER_THERMIA"
    };
    initializeLimits(tempratureLimits, tempratureMessages, tempLimits, tempMessages);
}

void initializePulseRateLimits() {
    std::vector<std::pair<float, float>> pulseLimits = {
        {std::numeric_limits<float>::min(), 60},
        {60, 100},
        {100, std::numeric_limits<float>::max()}
    };
    std::vector<std::string> pulseMessages = {
        "WARNING:BRADYCHARDIA",
        "NORMAL Pulse",
        "WARNING:TACHYCHARDIA"
    };
    initializeLimits(pulseRateLimits, pulseRateMessages, pulseLimits, pulseMessages);
}

void initializeSPo2Limits() {
    std::vector<std::pair<float, float>> spo2ParamLimits = {
        {std::numeric_limits<float>::min(), 80},
        {80, std::numeric_limits<float>::max()}
    };
    std::vector<std::string> spo2Messages = {
        "WARNING:HYPOXEMIA",
        "Normal SPO2"
    };
    initializeLimits(spo2Limits, spo2Messages, spo2ParamLimits, spo2Messages);
}

void writeMessage(std::string message) {
    std::cout << message << "\n";
}



bool isParameterNormal(double value,ParameterType type){
    switch(type){
        case TEMPERATURE:
             return isTempraturNormal(value);
        case PULSE_RATE:
             return isPulseNormal(value);
        case SPO2:
            return isSPO2Normal(value);
        }
    return false;        
}


bool isTempraturNormal(int value) {
    int cnt = 0;
    std::cout<<"value is :"<<value<<"\n";
    for (auto i = tempratureLimits.begin(); i != tempratureLimits.end(); i++) {
        if (i->first == std::numeric_limits<int>::min() && value < i->second) {
            writeMessage(tempratureMessages[0]);
            break;
        } else if (i->second == std::numeric_limits<int>::max() && value > i->first) {
            writeMessage(tempratureMessages[4]);
            break;
        } else if ((value >= i->first) && (value <= i->second)) {
            writeMessage(tempratureMessages[cnt]);
            break;
        }
        cnt++;
    }

    if (tempratureMessages[cnt].find("Normal") != std::string::npos) {
        return true;
    }
    return false;
}

bool isPulseNormal(float value) {
    int cnt = 0;
    for (auto i = pulseRateLimits.begin(); i != pulseRateLimits.end(); i++) {
        if (i->first == std::numeric_limits<float>::min() && value < i->second) {
            writeMessage(pulseRateMessages[0]);
            std::cout<<pulseRateMessages[0]<<"\n";
            break;
        } else if (i->second == std::numeric_limits<float>::max() && value > i->first) {
            writeMessage(pulseRateMessages[2]);
            std::cout<<pulseRateMessages[2]<<"\n";
            break;
        } else if ((value >= i->first) && (value <= i->second)) {
            writeMessage(pulseRateMessages[cnt]);
            std::cout<<pulseRateMessages[cnt]<<"\n";
            break;
        }
        cnt++;
    }
    if (pulseRateMessages[cnt].find("Normal") != std::string::npos) {
        return true;
    }
    return false;
}

bool isSPO2Normal(int value) {
    int cnt = 0;
    for (auto i = spo2Limits.begin(); i != spo2Limits.end(); i++) {
        if (i->first == std::numeric_limits<float>::min() && value < i->second) {
            writeMessage(spo2Messages[0]);
            break;
        } else if (i->second == std::numeric_limits<float>::max() && value > i->first) {
            writeMessage(spo2Messages[1]);
            break;
        } else if ((value >= i->first) && (value <= i->second)) {
            writeMessage(spo2Messages[cnt]);
            break;
        }
        cnt++;
    }
    if (spo2Messages[cnt].find("Normal") != std::string::npos) {
        return true;
    }
    return false;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    return isParameterNormal(temperature,ParameterType::TEMPERATURE) && isParameterNormal(pulseRate,ParameterType::PULSE_RATE) && isParameterNormal(spo2,ParameterType::SPO2);
}
