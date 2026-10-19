#include "./LedModel.h"

void LedModel::setRed(int value) {
    redPin = value;
}

int LedModel::getRed() {
    return redPin;
}

void LedModel::setGreen(int value) {
    greenPin = value;
}

int LedModel::getGreen() {
    return greenPin;
}

void LedModel::setBlue(int value) {
    bluePin = value;
}

int LedModel::getBlue() {
    return bluePin;
}