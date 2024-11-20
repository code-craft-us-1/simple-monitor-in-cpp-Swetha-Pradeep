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


struct TemperatureRange {
    double minTemp;
    double maxTemp;
    std::string message;
};
std::vector<TemperatureRange> tempranges;

void sleep() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}
/*int checkTemprature1(int temperature) {
    if (temperature > 102 || temperature < 95) {
        cout << "Temperature is critical!\n";
        sleep();
        return 0;
    }
    return 1;
}
*/

bool checkWithinRange(TemperatureRange &range,double temperature){
      return temperature >= range.minTemp && temperature <= range.maxTemp;
}

void initializeTemprature(){
    tempranges.push_back({102, INT_MAX, "Temperature is critically high!\n"});
    tempranges.push_back({100.48, 102, "Normal"});
    tempranges.push_back({96.54, 100.47, "Temperature is high!\n"});   
    tempranges.push_back({95, 96.53, "Temperature is critically high!\n"});   
    tempranges.push_back({INT_MIN, 95, "Temperature is critically low!\n"});    
    
}
std::string checkTemperature(double temperature) {
   
    initializeTemprature();
    
     
     auto it = std::find_if(tempranges.begin(), tempranges.end(), [temperature]( TemperatureRange tempranges) {
        return temperature >= tempranges.minTemp && temperature <= tempranges.maxTemp;
    });
    if(it!=tempranges.end()){
        return it->message;
    }
    return "";
    
   
    
}

int isTempratureNormal(double temperature) {
    return checkTemperature(temperature) == "Normal";
}

int checkPulserate(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        cout << "Pulse Rate is out of range!\n";
        sleep();
        return 0;
    }
    return 1;
}

int checkSPO2(float spo2) {
    if (spo2 < 90) {
        cout << "Oxygen Saturation out of range!\n";
        sleep();
        return 0;
    }
    return 1;
}
int vitalsOk(float temperature, float pulseRate, float spo2) {
    return isTempratureNormal(temperature) && checkPulserate(pulseRate) && checkSPO2(spo2);
}
