#include <Arduino.h>
#include "./controller/LoadCellController.h"
#include "./controller/JointsController.h"
#include "./controller/AccelerometerController.h"
#include "./model/OrthosisStates.h"
#include "./view/SerialView.h"
#include "./controller/ConfigController.h"
#include "./controller/BatteryController.h"
#include "./controller/LedController.h"

LoadCellController lcController;
JointsController jController;
AccelerometerController aController;
ConfigController configController;
BatteryController batteryController;
LedController ledController;

float baseline;
float movement;

float weight;

OrthosisStates state = OrthosisStates::IDLE;
OrthosisStates lastState = OrthosisStates::IDLE;
unsigned long lastBatteryPublish = 0;

void setup() {
    Serial.begin(115200);
    SerialView::beginSerial();

    ledController.setLed();

    configController.begin();
    configController.connect();

    batteryController.setConfigController(&configController);
    batteryController.begin();

    jController.begin();
    jController.initialize();

    lcController.begin();

    aController.begin();

    baseline = aController.getBaseline();
};

void loop() {
    configController.update();

    int batteryPercentage = batteryController.getBatteryPercentage();

    if (configController.isMqttConnected() && millis() - lastBatteryPublish >= 10000) {
        lastBatteryPublish = millis();
        configController.publishBattery(batteryPercentage);
    }
  
    if (!configController.hasAttemptedMqttConnection()) {
        if (WiFi.status() == WL_CONNECTED) {
            ledController.blinkConnecting();
        } else if (batteryPercentage < 20) {
            ledController.orange();
        } else {
            ledController.green();
        }
    } else if (configController.isMqttConnected()) {
        ledController.blue();
    } else if (WiFi.status() == WL_CONNECTED) {
        ledController.blinkConnecting();
    } else {
        ledController.green();
    }

    if (!configController.hasAttemptedMqttConnection()) {
        return;
    }

    if (configController.consumeCalibrationRequest()) {
        baseline = aController.calibrate();
        Serial.println("Accelerometer calibration complete.");
    }

    delay(15);

    movement = aController.getAz() - baseline;
    weight = lcController.getWeight();

    if (state == OrthosisStates::IDLE && movement > 0.01) {
        state = OrthosisStates::GETTINGFOOD;
    }else if (state == OrthosisStates::GETTINGFOOD && weight > 1.0) {
        state = OrthosisStates::EATING;
    }else if (state == OrthosisStates::EATING){
        delay(1500);
        state = OrthosisStates::GETTINGFOOD;
    }

    if (lastState != state) {
        if (state == OrthosisStates::GETTINGFOOD) {
            jController.getFood();       
        }else if (state == OrthosisStates::EATING) {
            delay(1500);
            jController.eat();
        }

        lastState = state;
    }
}
