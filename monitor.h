#pragma once
#include <list>
#include <utility>
#include <vector>
#include <string>
extern std::list<std::pair<int , int>> tempratureLimits;
extern std::vector<std::string> tempratureMessages;
extern std::list<std::pair<float , float>> pulseRateLimits;
extern std::vector<std::string> pulseRateMessages;
extern std::list<std::pair<float , float>> spo2Limits;
extern std::vector<std::string> spo2Messages;
void initializeTempratureLimits();

void initializePulseRateLimits();
void initializeSPo2Limits();
bool isTempraturNormal(int value);
bool isPulseNormal(float value);
bool isSPO2Normal(float value);

int vitalsOk(float temperature, float pulseRate, float spo2);
void sleep();
