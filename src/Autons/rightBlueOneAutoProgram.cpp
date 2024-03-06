#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace okapi;

void rightBlueOneAuton(void) {
	twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(70);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	flywheelMotor.moveVoltage(-5000);
	intakeMotor.moveVoltage(12000);
	to_zero(6000,12000,330);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	pros::delay(2000);
	to_zero(-7000,-12000,500);
	pros::delay(2000);
}