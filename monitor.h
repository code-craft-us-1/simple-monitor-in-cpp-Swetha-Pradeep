#pragma once
#include<string>
#include <vector>
struct ParameterRange {
    double minVal;
    double maxVal;
    std::string message;
};
//std::string checkTemperature(double temperature);
std::string checkParameter(double paramVal,std::vector<ParameterRange> paramranges);
void initializeTemprature(std::string language);
int isTempratureNormal(double temperature,std::string language);
void initializePulseRate(std::string language);
int isPulseNormal(double pulse,std::string language);
void initializeSpo2(std::string language);
int isSPo2Normal(double spo2,std::string language);
//int checkPulserate(float pulseRate);

int vitalsOk(float temperature, float pulseRate, float spo2,std::string language);
void sleep();
