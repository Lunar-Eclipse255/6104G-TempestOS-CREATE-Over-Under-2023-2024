#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace okapi;
#define WING_LEFT_DD 'C'
#define WING_RIGHT_DD 'D'
pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);

void pSkills(void) {
    twoBarOneMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
    twoBarTwoMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
    intakeMotor.moveVoltage(-12000);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
    to_zero(-10800,-12000,1500);
    driveChassis->turnAngle(-90_deg);
    to_zero(-12000,-3000,350);
    //driveChassis->moveDistance(-10_cm);
    driveChassis->turnAngle(0_deg);
    twoBarOneMotor.moveVoltage(-12000);
    twoBarTwoMotor.moveVoltage(-12000);
    pros::delay(200);
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
    printf("Rotation: %i\n",(cataRotate.get_angle()/100));
    flywheelMotor.moveVoltage(12000);
    while((cataRotate.get_angle()/100)<130){
        printf("Rotation: %i\n",(cataRotate.get_angle()/100));
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
    pros::delay(1000);
    to_zero(3000,-10000,500);
    //pros::delay(1000);
    pros::delay(25000);
    ///*
    driveChassis->moveDistance(20_cm);
    flywheelMotor.moveVoltage(0);
    while((cataRotate.get_angle()/100)>30){
        printf("Rotation: %i\n",(cataRotate.get_angle()/100));
        twoBarOneMotor.moveVoltage(12000);
        twoBarTwoMotor.moveVoltage(12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
    driveChassis->turnAngle(160_deg);
    driveChassis->moveDistance(45_cm);
    pros::delay(800);
    intakeMotor.moveVoltage(-12000);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
    driveChassis->moveDistance(-30_cm);

    driveChassis->turnAngle(-185_deg);
    to_zero(7500,10000,2900);
    driveChassis->moveDistance(10_cm);
    intakeMotor.moveVoltage(-12000);
    pros::delay(2500);
    intakeMotor.moveVoltage(0);
    driveChassis->moveDistance(-40_cm);
    driveChassis->turnAngle(106_deg);
    while(((cataRotate.get_angle()/100)>0)&&((cataRotate.get_angle()/100)<350)){
        printf("Rotation: %i\n",(cataRotate.get_angle()/100));
        twoBarOneMotor.moveVoltage(12000);
        twoBarTwoMotor.moveVoltage(12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
    to_zero(12000,10000,1500);
    to_zero(12000,1000,660);
    to_zero(6000,12000,1000);
    leftWingDD.set_value(true);
    rightWingDD.set_value(true);
    driveChassis->turnAngle(100_deg);
    to_zero(-9000,-12000,1000);
    driveChassis->moveDistance(65_cm);
    driveChassis->turnAngle(20_deg);
    driveChassis->moveDistance(-60_cm);
    driveChassis->moveDistance(65_cm);
    driveChassis->turnAngle(-40_deg);
    driveChassis->moveDistance(-70_cm);
    driveChassis->moveDistance(65_cm);
    leftWingDD.set_value(false);
    rightWingDD.set_value(false);
    //*/
}