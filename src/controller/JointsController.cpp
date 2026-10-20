#include "JointsController.h"
#include <Arduino.h>

void JointsController::begin(){
    joint1.setPin(18);
    joint2.setPin(17);
    joint3.setPin(16);

    joint1.attach();
    joint2.attach();
    joint3.attach();
}

void JointsController::initialize(){
    // for (int i = joint1.getAngle(); i >= 0; i--){
    //     joint1.setAngle(i);
    //     delay(10);
    // }

    // for (int i = joint2.getAngle(); i >= 0; i--){
    //     joint2.setAngle(i);
    //     delay(10);
    // }

    // for (int i = joint3.getAngle(); i >= 0; i--){
    //     joint3.setAngle(i);
    //     delay(10);
    // } 
    
    joint1.setAngle(0);
    joint2.setAngle(0);
    joint3.setAngle(0);
}

void JointsController::getFood(){
    if(joint1.getAngle() < 60){
        for (int i = joint1.getAngle(); i <= 60; i++){
            joint1.setAngle(i);
            delay(10);
        }
    }else if(joint1.getAngle() > 60){
        for (int i = joint1.getAngle(); i >= 60; i--){
            joint1.setAngle(i);
            delay(10);
        }
    }

    delay(30);

    if(joint2.getAngle() < 15){
        for (int i = joint2.getAngle(); i <= 15; i++){
            joint2.setAngle(i);
            delay(10);
        }
    }else if(joint2.getAngle() > 15){
        for (int i = joint2.getAngle(); i >= 15; i--){
            joint2.setAngle(i);
            delay(10);
        }
    }

    if(joint3.getAngle() < 0){
        for (int i = joint3.getAngle(); i <= 0; i++){
            joint3.setAngle(i);
            delay(10);
        }
    }else if(joint3.getAngle() > 0){
        for (int i = joint3.getAngle(); i >= 0; i--){
            joint3.setAngle(i);
            delay(10);
        }
    }
}

void JointsController::eat(){
    if(joint1.getAngle() < 85){
        for (int i = joint1.getAngle(); i <= 85; i++){
            joint1.setAngle(i);
            delay(10);
        }
    }else if(joint1.getAngle() > 85){
        for (int i = joint1.getAngle(); i >= 85; i--){
            joint1.setAngle(i);
            delay(10);
        }
    }

    if(joint2.getAngle() < 7){
        for (int i = joint2.getAngle(); i <= 7; i++){
            joint2.setAngle(i);
            delay(10);
        }
    }else if(joint2.getAngle() > 7){
        for (int i = joint2.getAngle(); i >= 7; i--){
            joint2.setAngle(i);
            delay(10);
        }
    }

    if(joint3.getAngle() < 35){
        for (int i = joint3.getAngle(); i <= 35; i++){
            joint3.setAngle(i);
            delay(10);
        }
    }else if(joint3.getAngle() > 35){
        for (int i = joint3.getAngle(); i >= 35; i--){
            joint3.setAngle(i);
            delay(10);
        }
    }
}