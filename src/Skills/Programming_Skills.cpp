#include "autons.hpp"
#include "display.hpp"
#include "motors.h"
#include "main.h"
#include "okapi/api.hpp"
#include "turn_voltage.hpp"
using namespace okapi;

void pSkills(void) {
twoBarOneMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
twoBarTwoMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
printf("Rotation: %i\n",(cataRotate.get_angle()/100));
  twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(70);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	flywheelMotor.moveVoltage(-5000);
	intakeMotor.moveVoltage(12000);
	to_zero(6000,12000,760);
    driveChassis->moveDistance(10_cm);

	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	pros::delay(500);
	to_zero(-4400,-12000,820);
    driveChassis->turnAngle(0_deg);
    flywheelMotor.moveVoltage(0);
	intakeMotor.moveVoltage(0);
    twoBarOneMotor.moveVoltage(12000);
	twoBarTwoMotor.moveVoltage(12000);
	pros::delay(100);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
    
    to_zero(-10000,-12000,1850);
    driveChassis->turnAngle(-90_deg);
    to_zero(-12000,-1000,350);
    driveChassis->turnAngle(0_deg);
    twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(200);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
    printf("Rotation: %i\n",(cataRotate.get_angle()/100));
    flywheelMotor.moveVoltage(12000);
    while((cataRotate.get_angle()/100)<130){
        printf("Rotation: %i\n",(cataRotate.get_angle()/100));
        twoBarOneMotor.moveVoltage(-12000);
        twoBarTwoMotor.moveVoltage(-12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
    pros::delay(1000);
    to_zero(3000,-10000,500);
    pros::delay(1000);
    driveChassis->moveDistance(20_cm);
    flywheelMotor.moveVoltage(0);
    while((cataRotate.get_angle()/100)>30){
        printf("Rotation: %i\n",(cataRotate.get_angle()/100));
        twoBarOneMotor.moveVoltage(12000);
        twoBarTwoMotor.moveVoltage(12000);
    }
    twoBarOneMotor.moveVoltage(0);
    twoBarTwoMotor.moveVoltage(0);
    driveChassis->turnAngle(170_deg);
    driveChassis->moveDistance(50_cm);
    pros::delay(1000);
    intakeMotor.moveVoltage(-12000);
    driveChassis->moveDistance(-30_cm);
    intakeMotor.moveVoltage(0);
    driveChassis->turnAngle(-170_deg);
    to_zero(7000,10000,3000);
    driveChassis->moveDistance(40_cm);
    intakeMotor.moveVoltage(12000);
    pros::delay(1000);
    intakeMotor.moveVoltage(0);
    driveChassis->moveDistance(-30_cm);


    

}