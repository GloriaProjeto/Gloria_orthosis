#pragma once

#include "../model/AccelerometerModel.h"
#include "../sensor/AccelerometerSensor.h"
#include "../view/SerialView.h"

class AccelerometerController{
    private:
        AccelerometerModel model;
        AccelerometerSensor sensor;
        SerialView view;

    public:
        void begin();
        float calibrate();
        float getAz();
        float getBaseline(); 
};