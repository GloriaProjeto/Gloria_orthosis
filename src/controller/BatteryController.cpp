#include "./BatteryController.h"

#include <Arduino.h>

void BatteryController::begin() {
    sensor.begin();
}

void BatteryController::setConfigController(ConfigController* controller) {
    configController = controller;
}

int BatteryController::getBatteryPercentage() {
    model.setPercentage(sensor.readBatteryPercentage());

    view.showBatteryPercentage(model.getPercentage());

    return model.getPercentage();
}