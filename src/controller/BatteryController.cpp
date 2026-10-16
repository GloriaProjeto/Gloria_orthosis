#include "./BatteryController.h"

#include <Arduino.h>

void BatteryController::begin() {
    sensor.begin();
}

void BatteryController::getBatteryPercentage() {
    model.getPercentage.readBatteryPercentage(sensor.readBatteryPercentage());

    view.showBatteryPercentage(model.getPercentage());

    configController.publishBattery(model.getPercentage());
}