#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
using namespace okapi;
pros::ADIDigitalOut leftWing (WING_LEFT);
pros::ADIDigitalOut rightWing (WING_RIGHT);
void pSkills(void) {

    driveChassis->setMaxVelocity(120);
    intakeMotor.moveVoltage(-12000);
	pros::delay(200);
    intakeMotor.moveVoltage(0);
    pros::delay(200);
    leftChassis.moveVoltage(-12000);
    rightChassis.moveVoltage(-7000);
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
    catapultMotor.moveVoltage(11000);
    pros::delay(35000);
    //pros::delay(850);
    //pros::delay(70000);
    catapultMotor.moveVoltage(0);
    driveChassis->setMaxVelocity(120);
    driveChassis->moveDistance(-10_cm);
    driveChassis->turnAngle(-48_deg); 
    rightChassis.moveVoltage(-11000);
    leftChassis.moveVoltage(-9000);
    pros::delay(1800);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(-11000);
    leftChassis.moveVoltage(-3000);
    pros::delay(1300);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(150);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    pros::delay(500);
    driveChassis->setMaxVelocity(600);
    driveChassis->turnAngle(-180_deg);
    driveChassis->setMaxVelocity(150);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    driveChassis->setMaxVelocity(80);
    leftWing.set_value(true);
    driveChassis->moveDistance(-80_cm);
    rightWing.set_value(true);
    driveChassis->turnAngle(-120_deg);
    intakeMotor.moveVoltage(-0);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(800);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    driveChassis->turnAngle(-45_deg);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(800);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    driveChassis->turnAngle(75_deg);
    rightChassis.moveVoltage(-12000);
    leftChassis.moveVoltage(-12000);
    pros::delay(800);
    rightChassis.moveVoltage(12000);
    leftChassis.moveVoltage(12000);
    pros::delay(700);
    rightChassis.moveVoltage(0);
    leftChassis.moveVoltage(0);
    leftWing.set_value(false);
    rightWing.set_value(false);  
}