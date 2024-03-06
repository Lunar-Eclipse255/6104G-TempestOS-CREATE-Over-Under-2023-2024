#include "main.h"
#include "motors.h"


    void to_zero(int voltageOne, int voltageTwo, int time){
            leftChassis.moveVoltage(voltageOne);
            rightChassis.moveVoltage(voltageTwo);
            pros::delay(time);
            leftChassis.moveVoltage(0);
            rightChassis.moveVoltage(0);
    }
    
    
    
    void to_value(int initialVoltageOne, int initialVoltageTwo, int time, int finalVoltageOne, int finalVoltageTwo){
            leftChassis.moveVoltage(initialVoltageOne);
            rightChassis.moveVoltage(initialVoltageTwo);
            pros::delay(time);
            leftChassis.moveVoltage(finalVoltageOne);
            rightChassis.moveVoltage(finalVoltageTwo);
    }
    void to_value(int initialVoltageOne, int initialVoltageTwo, int time, int finalVoltageOne, int finalVoltageTwo, bool flipped){
            leftChassis.moveVoltage(initialVoltageTwo);
            rightChassis.moveVoltage(initialVoltageOne);
            pros::delay(time);
            leftChassis.moveVoltage(finalVoltageTwo);
            rightChassis.moveVoltage(finalVoltageOne);
    }
