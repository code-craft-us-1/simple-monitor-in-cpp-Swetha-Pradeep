#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <climits>
#include <vector>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;


struct ParameterRange {
    double minVal;
    double maxVal;
    std::string message;
};
std::vector<ParameterRange> tempranges;
std::vector<ParameterRange> pulseranges;
std::vector<ParameterRange> spo2ranges;

void sleep() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

void initializeTemprature(){
    tempranges.push_back({102, INT_MAX, "HYPER_THERMIA!\n"});
    tempranges.push_back({100.48, 102, "WARNING:NEAR_HYPER!\n"});
    tempranges.push_back({96.54, 100.47, "Normal"});   
    tempranges.push_back({95, 96.53, "Warning:NEAR_HYPO!\n"});   
    tempranges.push_back({INT_MIN, 95, "Warning:HYPO_THERMIA!\n"});    
    
}

void initializePulseRate(){
    pulseranges.push_back({60, 100, "Normal"});
    pulseranges.push_back({INT_MIN, 60, "WARNING:BRADYCARDIA!\n"});
    pulseranges.push_back({100, INT_MAX, "WARNING:TACHYCARDIA!\n"});
}
std::string checkParameter(double paramVal,std::vector<ParameterRange> paramranges) {
      
     auto it = std::find_if(paramranges.begin(), paramranges.end(), [paramVal]( ParameterRange paramranges) {
        return paramVal >= paramranges.minVal && paramVal <= paramranges.maxVal;
    });
    if(it!=paramranges.end()){
        return it->message;
    }
    return "";
    
}

int isTempratureNormal(double temperature) {
    initializeTemprature();
    return checkParameter(temperature,tempranges) == "Normal";
}

int isPulseNormal(double pulse) {
    initializePulseRate();
    return checkParameter(pulse,pulseranges) == "Normal";
}

/*int checkPulserate(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        cout << "Pulse Rate is out of range!\n";
        sleep();
        return 0;
    }
    return 1;
}*/

int checkSPO2(float spo2) {
    if (spo2 < 90) {
        cout << "Oxygen Saturation out of range!\n";
        sleep();
        return 0;
    }
    return 1;
}
int vitalsOk(float temperature, float pulseRate, float spo2) {
    return isTempratureNormal(temperature) && isPulseNormal(pulseRate) && checkSPO2(spo2);
}
