#pragma once

class BatterySensor{
    private:
        const int pin = 34;
        const float voltageDividerRatio = 5.0f;
    public:
        void begin();
        int readBatteryPercentage();
};