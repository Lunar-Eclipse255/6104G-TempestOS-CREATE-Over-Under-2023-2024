#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"
#include "turn_voltage.hpp"
//#include "okapi/api.hpp"

using namespace okapi;

void leftRedOneAuton(void) {
	intakeMotor.moveVoltage(-12000);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
	twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(70);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	flywheelMotor.moveVoltage(-4000);
	intakeMotor.moveVoltage(12000);
	to_zero(12000,6000,650);
	driveChassis->moveDistance(10_cm);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	pros::delay(2000);
	to_zero(-12000,-5000,700);
	pros::delay(2000);
	flywheelMotor.moveVoltage(0);
	intakeMotor.moveVoltage(0);
	



}