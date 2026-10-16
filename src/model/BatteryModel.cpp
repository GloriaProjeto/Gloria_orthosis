#include "./BatteryModel.h"

int BatteryModel::getPercentage() {
    return this->percentage;
}

void BatteryModel::setPercentage(int percentage) {
    this->percentage = percentage;
}

float BatteryModel::getVoltage() {
    return this->voltage;
}

void BatteryModel::setVoltage(float voltage) {
    this->voltage = voltage;
}