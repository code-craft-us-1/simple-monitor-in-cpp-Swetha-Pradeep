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

void initializeTemprature(std::string language){

    if(language=="English"){
        tempranges.push_back({102, INT_MAX, "HYPER_THERMIA!\n"});
        tempranges.push_back({100.48, 102, "WARNING:NEAR_HYPER!\n"});
        tempranges.push_back({96.54, 100.47, "Normal"});   
        tempranges.push_back({95, 96.53, "Warning:NEAR_HYPO!\n"});   
        tempranges.push_back({INT_MIN, 95, "Warning:HYPO_THERMIA!\n"});    
    }
    else if(language=="German"){
        tempranges.push_back({102, INT_MAX, "Hyperthermie!\n"});
        tempranges.push_back({100.48, 102, "Warnung:in der Nähe von Hyperthermie!\n"});
        tempranges.push_back({96.54, 100.47, "Normal"});   
        tempranges.push_back({95, 96.53, "Warnung:nahe der Hypothermie!\n"});   
        tempranges.push_back({INT_MIN, 95, "Warnung:Hypothermie!\n"});    
    }
    
}

void initializePulseRate(std::string language){

    if(language =="English"){
        pulseranges.push_back({60, 100, "Normal"});
        pulseranges.push_back({INT_MIN, 60, "Warning:Bradycardia!\n"});
        pulseranges.push_back({100, INT_MAX, "Warning:Tachycardia!\n"});
    }
    else if(language=="German"){
        pulseranges.push_back({60, 100, "Normal"});
        pulseranges.push_back({INT_MIN, 60, "Warnung:Bradykardie!\n"});
        pulseranges.push_back({100, INT_MAX, "Warnung:Tachykardie!\n"});
    }
    
}

void initializeSpo2(std::string language){
    if(language=="English"){
        spo2ranges.push_back({80, INT_MAX, "Normal"});
        spo2ranges.push_back({INT_MIN, 80, "Warning:Hypoxemia!\n"});
    }
    else if(language=="German"){
        spo2ranges.push_back({80, INT_MAX, "Normal"});
        spo2ranges.push_back({INT_MIN, 80, "Warnung:Hypoxämie!\n"});
    }
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

int isTempratureNormal(double temperature,std::string language) {
    initializeTemprature(language);
    return checkParameter(temperature,tempranges) == "Normal";
}

int isPulseNormal(double pulse,std::string language) {
    initializePulseRate(language);
    return checkParameter(pulse,pulseranges) == "Normal";
}

int isSPo2Normal(double spo2,std::string language) {
    initializeSpo2(language);
    return checkParameter(spo2,spo2ranges) == "Normal";
}

int vitalsOk(float temperature, float pulseRate, float spo2,std::string language) {
    return isTempratureNormal(temperature,language) && isPulseNormal(pulseRate,language) && isSPo2Normal(spo2,language);
}
