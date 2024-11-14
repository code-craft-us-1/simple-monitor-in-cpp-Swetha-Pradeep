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
#include <functional>
#include <unordered_map>
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
template <typename T>
bool isMinLimit(T value, const std::pair<T,T>& limit, const std::string& message) {
    if (limit.first == std::numeric_limits<T>::min() && value < limit.second) {
        writeMessage(message);
        return true;
    }
    return false;
}
template <typename T>
bool isMaxLimit(T value, const std::pair<T,T>& limit, const std::string& message) {
    if (limit.second == std::numeric_limits<T>::max() && value > limit.first) {
        writeMessage(message);
        return true;
    }
    return false;
}

template<typename T>
bool isWithinLimit(T value, const std::pair<T,T>& limit, const std::string& message) {
    if (value >= limit.first && value <= limit.second) {
        writeMessage(message);
        return true;
    }
    return false;
}

bool isParameterNormal(double value, ParameterType type) {
    static const std::unordered_map<ParameterType, std::function<bool(double)>> checkFunctions = {
        { TEMPERATURE, [](double v) { return isTempraturNormal(static_cast<int>(v)); } },
        { PULSE_RATE, [](double v) { return isPulseNormal(static_cast<float>(v)); } },
        { SPO2, [](double v) { return isSPO2Normal(static_cast<float>(v)); } }
    };

    auto it = checkFunctions.find(type);
    if (it != checkFunctions.end()) {
        return it->second(value);
    }
    return false;
}


bool isTempraturNormal(int value) {
    int cnt = 0;
    for (const auto& limit : tempratureLimits) {
        if (isMinLimit(value, limit, tempratureMessages[0])){
            break;
        } 
        else if(isMaxLimit(value, limit, tempratureMessages[4])){
            break;
        }
        else if(isWithinLimit(value, limit, tempratureMessages[cnt])) {
            break;
        } 
        cnt++;
    }

    return tempratureMessages[cnt].find("Normal") != std::string::npos;
}


bool isPulseNormal(float value) {
    int cnt = 0;
   for (const auto& limit : pulseRateLimits) {
        if (isMinLimit(value, limit, pulseRateMessages[0])){
            break;
        } 
        else if(isMaxLimit(value, limit, pulseRateMessages[4])){
            break;
        }
        else if(isWithinLimit(value, limit, pulseRateMessages[cnt])){
            break;
        }
        cnt++;
    }
    return pulseRateMessages[cnt].find("Normal") != std::string::npos;
   
}

bool isSPO2Normal(float value) {
    int cnt = 0;
    for (const auto& limit : spo2Limits) {
        if (isMinLimit(value, limit, spo2Messages[0])){
            break;
        } 
        else if(isMaxLimit(value, limit, spo2Messages[2])){
            break;
        }
        cnt++;
    }
    return spo2Messages[cnt].find("Normal") != std::string::npos;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    return isParameterNormal(temperature,ParameterType::TEMPERATURE) && isParameterNormal(pulseRate,ParameterType::PULSE_RATE) && isParameterNormal(spo2,ParameterType::SPO2);
}
