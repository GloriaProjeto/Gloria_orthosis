#pragma once 

#include "../model/BatteryModel.h"
#include "../sensor/BatterySensor.h"
#include "../controller/ConfigController.h"
#include "../view/SerialView.h"

class BatteryController{
    private:
        BatteryModel model;
        BatterySensor sensor;
        ConfigController configController;
        SerialView view;

    public:
        void begin();
        int getBatteryPercentage();
};