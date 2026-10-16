#include "AccelerometerController.h"

void AccelerometerController::begin(){
    sensor.initialize();

    view.showAccelerometerConnection(sensor.testConnection());

    calibrate();
};

float AccelerometerController::calibrate(){
    float baseline = sensor.calibrateSensor();
    model.setBaseline(baseline);
    return baseline;
};

float AccelerometerController::getAz(){
    float az = sensor.readAz();

    model.setAz(az);

    view.showAz(model.getAz() - model.getBaseline());
    
    return model.getAz();
};

float AccelerometerController::getBaseline(){
    return model.getBaseline();
};