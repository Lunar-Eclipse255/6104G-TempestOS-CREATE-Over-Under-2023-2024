#include "main.h"
#include "motors.h"

void rotation_to_angle(int angle){
    if ((cataRotate.get_angle()/100)>350){
        cataRotate.reset_position();
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
        pros::delay(100);
        twoBarOneMotor.moveVoltage(0);
        twoBarTwoMotor.moveVoltage(0);
    }
    while((cataRotate.get_angle()/100)<=angle){
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
}
void rotation_to_angle(int angle, bool flipped){
    if ((cataRotate.get_angle()/100)>350){
        cataRotate.reset_position();
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
        pros::delay(100);
        twoBarOneMotor.moveVoltage(0);
        twoBarTwoMotor.moveVoltage(0);
    }
    while((cataRotate.get_angle()/100)>=angle){
        twoBarOneMotor.moveVoltage(12000);
        twoBarTwoMotor.moveVoltage(12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
}
void rotation_to_angle(int angle, int voltage){
    if ((cataRotate.get_angle()/100)>350){
        cataRotate.reset_position();
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
        pros::delay(100);
        twoBarOneMotor.moveVoltage(0);
        twoBarTwoMotor.moveVoltage(0);
    }
    while((cataRotate.get_angle()/100)<=angle){
        twoBarOneMotor.moveVoltage(voltage);
        twoBarTwoMotor.moveVoltage(voltage);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
}
void rotation_to_angle(int angle, int voltage, bool flipped){
    if ((cataRotate.get_angle()/100)>350){
        cataRotate.reset_position();
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
        pros::delay(100);
        twoBarOneMotor.moveVoltage(0);
        twoBarTwoMotor.moveVoltage(0);
    }
    while((cataRotate.get_angle()/100)>=angle){
        twoBarOneMotor.moveVoltage(voltage);
        twoBarTwoMotor.moveVoltage(voltage);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
}