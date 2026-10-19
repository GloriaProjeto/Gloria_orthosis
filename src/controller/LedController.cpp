#include "LedController.h"
#include <Arduino.h>

void LedController::setPins(int redPin, int greenPin, int bluePin) {
    ledModel.setRed(redPin);
    ledModel.setGreen(greenPin);
    ledModel.setBlue(bluePin);
}

void LedController::setLed() {
    const int redPin = 15;
    const int greenPin = 19;
    const int bluePin = 23;

    setPins(redPin, greenPin, bluePin);

    pinMode(ledModel.getRed(), OUTPUT);
    pinMode(ledModel.getGreen(), OUTPUT);
    pinMode(ledModel.getBlue(), OUTPUT);

    turnOff();
};

void LedController::turnOff() {
    digitalWrite(ledModel.getRed(), LOW);
    digitalWrite(ledModel.getGreen(), LOW);
    digitalWrite(ledModel.getBlue(), LOW);
};

void LedController::blue() {
    digitalWrite(ledModel.getRed(), LOW);
    digitalWrite(ledModel.getGreen(), LOW);
    digitalWrite(ledModel.getBlue(), HIGH);
};

void LedController::red() {
    digitalWrite(ledModel.getRed(), HIGH);
    digitalWrite(ledModel.getGreen(), LOW);
    digitalWrite(ledModel.getBlue(), LOW);
};

void LedController::green() {
    digitalWrite(ledModel.getRed(), LOW);
    digitalWrite(ledModel.getGreen(), HIGH);
    digitalWrite(ledModel.getBlue(), LOW);
};

void LedController::orange() {
    digitalWrite(ledModel.getRed(), HIGH);
    digitalWrite(ledModel.getGreen(), LOW);
    digitalWrite(ledModel.getBlue(), HIGH);
};

void LedController::blinkConnecting() {
    static unsigned long lastBlink = 0;
    static bool redOn = false;

    const unsigned long interval = 250;
    const unsigned long now = millis();

    if (now - lastBlink < interval) {
        return;
    }

    lastBlink = now;
    redOn = !redOn;

    if (redOn) {
        red();
    } else {
        blue();
    }
};




