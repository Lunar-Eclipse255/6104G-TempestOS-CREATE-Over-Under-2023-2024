#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "paths.hpp"
#include "turn_voltage.hpp"
//#include "okapi/api.hpp"

using namespace okapi;

void leftRedOneAuton(void) {
	twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(70);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	flywheelMotor.moveVoltage(-5000);
	intakeMotor.moveVoltage(12000);
	to_zero(12000,6000,330);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	pros::delay(2000);
	to_zero(-12000,-7000,500);
	pros::delay(2000);
	to_zero(-5000,5000,300);
	



}