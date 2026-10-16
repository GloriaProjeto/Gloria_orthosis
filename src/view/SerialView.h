#pragma once


class SerialView{
    public:
        static void beginSerial();

        void showWeight(float weight);
        void showAccelerometerConnection(bool connected);
        void showAz(float az);   
        void showBatteryPercentage(int percentage);
};
