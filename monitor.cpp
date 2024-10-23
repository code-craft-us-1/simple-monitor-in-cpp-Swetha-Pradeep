#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

void sleep() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

bool checkThreshold(int lowThresh, int highThresh,float value) {
    if ((value > highThresh) || (value < lowThresh)) {
        return true;
    }
    return false;
}
int checkTemprature(int temperature) {
    if (checkThreshold(95, 102, temperature)) {
        cout<< "Temperature is critical!\n";
        sleep();
        return 0;
   }
   /* if (temperature > 102 || temperature < 95) {
        cout << "Temperature is critical!\n";
        sleep();
        return 0;
    }*/
    return 1;
}

int checkPulserate(float pulseRate) {
    
    if (checkThreshold(60, 100, pulseRate)) {
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
    return checkTemprature(temperature) && checkPulserate(pulseRate) && checkSPO2(spo2);
}
