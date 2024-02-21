#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"
//#include "okapi/api.hpp"

//using namespace okapi; might be required

void rightBlueTwoAuton(void) {
	driveChassis->setMaxVelocity(120);
	intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
	rightWing.set_value(true);
	rightChassis.moveVoltage(-5500);
	leftChassis.moveVoltage(-12000);
	pros::delay(300);
	rightWing.set_value(false);
	pros::delay(200);
	rightChassis.moveVoltage(-8000);
	leftChassis.moveVoltage(-12000);
	pros::delay(400);
	rightChassis.moveVoltage(12000);
	leftChassis.moveVoltage(12000);
	pros::delay(200);
	rightChassis.moveVoltage(-12000);
	leftChassis.moveVoltage(-12000);
	pros::delay(600);
	rightChassis.moveVoltage(12000);
	leftChassis.moveVoltage(12000);
	pros::delay(300);
	rightChassis.moveVoltage(-12000);
	leftChassis.moveVoltage(-12000);
	pros::delay(600);
	rightChassis.moveVoltage(0);
	leftChassis.moveVoltage(0);
	driveChassis->moveDistance(20_cm);
	catapultMotor.moveVoltage(12000);
	pros::delay(350);
	catapultMotor.moveVoltage(0);
}
