#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

void leftBlueOneAuton(void) {

    driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
	rightChassis.moveVoltage(-12000);
	leftChassis.moveVoltage(-2000);
	pros::delay(300);
	leftWing.set_value(true);
	rightChassis.moveVoltage(8000);
	leftChassis.moveVoltage(500);
	pros::delay(500);
	rightChassis.moveVoltage(0);
	leftChassis.moveVoltage(0);
	//driveChassis->moveDistance(-5_cm);
	driveChassis->setMaxVelocity(600);
	driveChassis->turnAngle(-150_deg);
	driveChassis->turnAngle(68_deg);
	intakeMotor.moveVoltage(-12000);
	driveChassis->moveDistance(45_cm);
	leftWing.set_value(false);
	pros::delay(100);
	driveChassis->turnAngle(-47_deg);
	driveChassis->setMaxVelocity(120);
	driveChassis->moveDistance(69_cm);
	blocker.set_value(true);
	catapultMotor.moveVoltage(12000);
	pros::delay(350);
	catapultMotor.moveVoltage(0);    
}