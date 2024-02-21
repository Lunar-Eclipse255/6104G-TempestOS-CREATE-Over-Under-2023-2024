#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"


//#include "okapi/api.hpp"

using namespace okapi;

void dSkills(void) {
	driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    pros::delay(200);
    leftChassis.moveVoltage(-12000);
    rightChassis.moveVoltage(-6000);
    pros::delay(1000);
    leftChassis.moveVoltage(6000);
    rightChassis.moveVoltage(6000);
    pros::delay(400);
    leftChassis.moveVoltage(-6000);
    rightChassis.moveVoltage(-6000);
    pros::delay(800);
    
    leftChassis.moveVoltage(6000);
    rightChassis.moveVoltage(6000);
    
    pros::delay(800);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(0);
    driveChassis->setMaxVelocity(50);
    driveChassis->turnAngle(-85_deg);
    driveChassis->moveDistance(5_cm);
	
}



