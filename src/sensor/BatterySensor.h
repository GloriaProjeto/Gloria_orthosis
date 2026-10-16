#pragma once

class BatterySensor{
    private:
        const int pin = 0; // Pin's not already defined by the team. It will be soon.
        const float voltageDividerRatio = 5.0f;
    public:
        void begin();
        int readBatteryPercentage();
}