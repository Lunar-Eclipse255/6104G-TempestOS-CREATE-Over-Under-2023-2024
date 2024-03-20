#ifndef AUTOPROGRAMS_H
#define AUTOPROGRAMS_H

#include "display/lvgl.h"
#include "okapi/api.hpp"

extern pros::ADIDigitalOut leftWingCurved;
extern pros::ADIDigitalOut rightWingCurved;
extern pros::ADIDigitalOut leftWingDD;
extern pros::ADIDigitalOut rightWingDD;
extern pros::ADIDigitalOut sideHang;
//Declares the autonomous and skills functions
void leftRedOneAuton(void);
void leftBlueOneAuton(void);
void leftRedTwoAuton(void);
void leftBlueTwoAuton(void);
void rightRedOneAuton(void);
void rightBlueOneAuton(void);
void rightRedTwoAuton(void);
void rightBlueTwoAuton(void);
void disabledAuton(void);
void elimMatchRightAuton(void);
void elimMatchLeftAuton(void);
void pSkills(void);
void dSkills(void);


#endif
