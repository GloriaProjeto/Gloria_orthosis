#pragma once

#include "../model/LedModel.h"

class LedController {
    private:
        LedModel ledModel;

        void setPins(int redPin, int greenPin, int bluePin);
    public:
        void blue();
        void red();
        void green();
        void orange();

        void setLed();
        void blinkConnecting();
        void turnOff();
};