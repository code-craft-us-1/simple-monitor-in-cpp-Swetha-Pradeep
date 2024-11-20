#pragma once
#include<string>
//std::string checkTemperature(double temperature);
std::string checkParameter(double paramVal,std::vector<ParameterRange> paramranges);
int isTempratureNormal(double temperature);
int isPulseNormal(double pulse);
//int checkPulserate(float pulseRate);
int checkSPO2(float spo2);
int vitalsOk(float temperature, float pulseRate, float spo2);
void sleep();
