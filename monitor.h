#pragma once
#include <list>
#include <utility>
#include <vector>
#include <string>
std::list<std::pair<int , int>> tempratureLimits;
std::vector<std::string> tempratureMessages;
std::list<std::pair<float , float>> pulseRateLimits;
std::vector<std::string> pulseRateMessages;
std::list<std::pair<float , float>> spo2Limits;
std::vector<std::string> spo2Messages;
void initializeTempratureLimits();

void initializePulseRateLimits();
void initializeSPO2Limits();
bool isTempraturNormal(int value);
bool isPulseNormal(float value);
bool isSPO2Normal(int value);

int vitalsOk(float temperature, float pulseRate, float spo2);
void sleep();
