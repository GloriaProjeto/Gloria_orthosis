#pragma once 

#include "../model/BatteryModel.h"
#include "../sensor/BatterySensor.h"
#include "../controller/ConfigController.h"
#include "../view/SerialView.h"

class BatteryController{
    private:
        BatteryModel model;
        BatterySensor sensor;
        ConfigController* configController = nullptr;
        SerialView view;

    public:
        void begin();
        void setConfigController(ConfigController* controller);
        int getBatteryPercentage();
};