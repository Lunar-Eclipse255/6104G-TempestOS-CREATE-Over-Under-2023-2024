#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

void elimMatchLeftAuton(void) {

    driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(12000);
    rightChassis.moveVoltage(9000);
    leftChassis.moveVoltage(12000);
    pros::delay(550);
    rightChassis.moveVoltage(9000);
    leftChassis.moveVoltage(0);
    pros::delay(400);
    rightChassis.moveVoltage(0);
    driveChassis->moveDistance(31_cm);
    rightWing.set_value(true);
    driveChassis->moveDistance(-5_cm);
    driveChassis->turnAngle(90_deg);
    driveChassis->moveDistance(20_cm);
    driveChassis->turnAngle(90_deg);
    rightChassis.moveVoltage(4000);
    leftChassis.moveVoltage(12000);
    pros::delay(930);
    leftChassis.moveVoltage(-500);
    
    rightChassis.moveVoltage(12000);
     pros::delay(1000);
     rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    //driveChassis->turnAngle(10_deg);
    rightWing.set_value(false);
    intakeMotor.moveVoltage(-12000);
    driveChassis->setMaxVelocity(600);
    driveChassis->turnAngle(15_deg);
    driveChassis->moveDistance(75_cm);
    catapultMotor.moveVoltage(12000);
	pros::delay(350);
	catapultMotor.moveVoltage(0); 
    

    //driveChassis->turnAngle(-90_deg);
    //driveChassis->moveDistance(60_cm);
}