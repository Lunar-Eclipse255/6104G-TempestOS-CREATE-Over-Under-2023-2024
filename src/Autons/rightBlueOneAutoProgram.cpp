#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace okapi;

void rightBlueOneAuton(void) {
	intakeMotor.moveVoltage(-12000);
    pros::delay(200);
    intakeMotor.moveVoltage(0);
	twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(70);
	intakeMotor.moveVoltage(12000);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	to_zero(12000,5000,600);
	driveChassis->moveDistance(30_cm);
	pros::delay(100);
	driveChassis->turnAngle(-40_deg);
	flywheelMotor.moveVoltage(0);
	//intakeMotor.moveVoltage(0);
}
