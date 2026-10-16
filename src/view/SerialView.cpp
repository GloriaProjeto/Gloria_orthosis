#include "SerialView.h"
#include <Arduino.h>

namespace {
    void writeLine(const String& message){
        Serial.println(message);
    }
}

void SerialView::beginSerial(){
    writeLine("Local serial started");
}

void SerialView::showWeight(float weight){
    writeLine(String("Weight: ") + String(weight) + "g");
};

void SerialView::showAccelerometerConnection(bool connected){
    if(connected){
        writeLine("Accelerometer connected successfully");
    }else{
        writeLine("Failed in connecting accelerometer");
    }
};

void SerialView::showAz(float az){
    writeLine(String("AZ: ") + String(az));
};

void SerialView::showBatteryPercentage(int percentage){
    writeLine(String("Battery: ") + String(percentage) + "%");
};
