#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;

void elimMatchRightAuton(void) {
    driveChassis->setMaxVelocity(120);
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
    rightChassis.moveVoltage(1000);
    leftChassis.moveVoltage(12000);
    pros::delay(710);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    intakeMotor.moveVoltage(12000);
    driveChassis->moveDistance(120_cm);
    driveChassis->turnAngle(150_deg);
    rightWing.set_value(true);
    intakeMotor.moveVoltage(-12000);
    driveChassis->moveDistance(40_cm);
    
    driveChassis->turnAngle(40_deg);

    rightWing.set_value(false);
    driveChassis->setMaxVelocity(600);
    driveChassis->moveDistance(-10_cm);
    intakeMotor.moveVoltage(12000);
    driveChassis->turnAngle(220_deg);
    //driveChassis->moveDistance(45_cm);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(400);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
     rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(200);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    //driveChassis->turnAngle(-250_deg);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(500);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    //driveChassis->moveDistance(30_cm);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(220);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    intakeMotor.moveVoltage(-12000);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(200);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    pros::delay(300);
    intakeMotor.moveVoltage(0);
    
    driveChassis->turnAngle(220_deg);
    leftWing.set_value(true);
    rightWing.set_value(true);
    driveChassis->setMaxVelocity(600);
    
    //driveChassis->moveDistance(-40_cm);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    //driveChassis->moveDistance(30_cm);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(350);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    catapultMotor.moveVoltage(12000);
	pros::delay(350);
	catapultMotor.moveVoltage(0);
    
}