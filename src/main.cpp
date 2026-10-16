#include <Arduino.h>
#include "./controller/LoadCellController.h"
#include "./controller/JointsController.h"
#include "./controller/AccelerometerController.h"
#include "./model/OrthosisStates.h"
#include "./view/SerialView.h"
#include "./controller/ConfigController.h"
#include "./controller/BatteryController.h"

LoadCellController lcController;
JointsController jController;
AccelerometerController aController;
ConfigController configController;
BatteryController batteryController;

float baseline;
float movement;

float weight;

OrthosisStates state = OrthosisStates::IDLE;
OrthosisStates lastState = OrthosisStates::IDLE;

void setup() {
    Serial.begin(115200);
    SerialView::beginSerial();

    configController.begin();
    configController.connect();

    batteryController.begin();

    jController.begin();
    jController.initialize();

    lcController.begin();

    aController.begin();

    baseline = aController.getBaseline();
};

void loop() {
    configController.update();
    batteryController.getBatteryPercentage();

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
