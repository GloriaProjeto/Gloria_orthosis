#pragma once

class BatteryModel{
    private:
        float voltage = 0;
        int percentage = 0;

    public:
        void setVoltage(float newVoltage);
        void setPercentage(int newPercentage);
        float getVoltage();
        int getPercentage();
};