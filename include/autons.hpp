#ifndef AUTOPROGRAMS_H
#define AUTOPROGRAMS_H

#include "display/lvgl.h"
#include "okapi/api.hpp"

extern pros::ADIDigitalOut leftWing;
extern pros::ADIDigitalOut rightWing;
extern pros::ADIDigitalOut blocker;
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
