#ifndef DISPLAY_H
#define DISPLAY_H

#include "display/lvgl.h"
#include "main.h"
#include "gif-pros/gifclass.hpp"

//Declares an integer and functions.
extern int selectedProfile;
void MainLVGL();
static lv_res_t button_click_event(lv_obj_t* button);
void switchToScreen(lv_obj_t* screen);
void display(void);
void runSelectedAuto(void);
void display(void);
void runSelectedGIF(void);
extern int selectedProgram;
extern int autoType;

//Sets an enumeration type for autonomous type
typedef enum autonomous_type {
  AUTONOMOUS_RED = 0,
  AUTONOMOUS_BLUE = 1,
  AUTONOMOUS_SKILLS = 2
} autonomous_type_e_t;

#endif