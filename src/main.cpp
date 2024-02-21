#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
//defines adi ports for pistons
#define BLOCKER 'A'
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
#define SIDE_HANG 'D'
#define BAR_HANG 'E'




//A callback function for LLEMU's center button. When this callback is fired, it will toggle line 2 of the LCD text between "I was pressed!" and nothing. 
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

//Initializes the drive motors to what port a motor is plugged into and if its reversed
Motor backLeftDriveMotor (-10);
Motor middleLeftDriveMotor (-9);
Motor frontLeftDriveMotor (-8);
Motor backRightDriveMotor (20);
Motor middleRightDriveMotor (19);
Motor frontRightDriveMotor (18);
auto cataDistance = DistanceSensor(12);


//Sets up which side of the bot motors are in.
MotorGroup leftChassis ({backLeftDriveMotor,middleLeftDriveMotor,frontLeftDriveMotor});
MotorGroup rightChassis ({backRightDriveMotor, middleRightDriveMotor, frontRightDriveMotor});

//Initializes the drive chassis
std::shared_ptr<ChassisController> driveChassis =
	ChassisControllerBuilder()
		//.withMotors(leftChassis,rightChassis)
		//Sets which motors to use
		.withMotors(
			leftChassis,
			rightChassis
		)
		
		// Green cartridge, 3.25 in wheel diam, 17 in wheel track, 36:60 gear ratio.
		.withDimensions({AbstractMotor::gearset::green, (36.0 / 60.0)}, {{3.25_in, 10.5_in}, imev5GreenTPR})
		//{0.002, 0.001, 0.0001}  
		
		
		
		.withLogger(
        	std::make_shared<Logger>(
            	TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
            	"/ser/sout", // Output to the PROS terminal
            	Logger::LogLevel::debug // Most verbose log level
        	)
		)
		.build();

//Initializes the subsytem motors as well as the Adi Button
Motor intakeMotor(-5);
Motor catapultMotor (7);


//Declares variables for state checks.
bool wingCheckLeft;
bool sideHangCheck;
bool barHangCheck;
bool wingCheckRight;
bool blockerCheck;
bool cataToggle;

//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//initializers the check varibles to false
	wingCheckLeft=false;
	wingCheckRight=false;
	sideHangCheck = false;
	barHangCheck = false;
	blockerCheck=false;
	cataToggle=false;
	//pros::lcd::initialize();
	//initializes sylib
   	sylib::initialize();
	pros::ADIDigitalOut leftWing (WING_LEFT);
	pros::ADIDigitalOut rightWing (WING_RIGHT);
	pros::ADIDigitalOut sideHang (SIDE_HANG);
	pros::ADIDigitalOut blocker (BLOCKER);
	pros::ADIDigitalOut barHang (BAR_HANG);
	//Digitally Builds the Chassis
	
}


//Runs while the robot is in the disabled state of Field Management System or the VEX Competition Switch, following either autonomous or opcontrol. When the robot is enabled, this task will exit.
void disabled() {
	
}


//Runs after initialize(), and before autonomous when connected to the Field Management System or the VEX Competition Switch. This is intended for competition-specific initialization routines, such as an autonomous selector on the LCD. This task will exit when the robot is enabled and autonomous or opcontrol starts.
void competition_initialize() {
	// Set up LVGL display
	MainLVGL();
}


//Runs the user autonomous code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the autonomous mode. Alternatively, this function may be called in initialize or opcontrol for non-competition testing purposes. If the robot is disabled or communications is lost, the autonomous task will be stopped. Re-enabling the robot will restart the task, not re-start it from where it left off.
void autonomous() {
	//initializes the lcd for pros
	//pros::lcd::initialize();
	runSelectedGIF();
	//runs the selected autonomous/skills program
	runSelectedAuto();
	//pSkills();
	//rightBlueOneAuton();
	//elimMatchRightAuton();
	}
	
//Runs the operator control code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If no competition control is connected, this function will run immediately following initialize(). If the robot is disabled or communications is lost, the operator control task will be stopped. Re-enabling the robot will restart the task, not resume it from where it left off.
void opcontrol() {
	if ((autoType == AUTONOMOUS_SKILLS)&&(selectedProgram==1)){
		dSkills();
	}
	
	driveChassis->setMaxVelocity(600);
	//clears screen
	//lv_init();
	//Testing: MainLVGL();
	//MainLVGL();
	pros::ADIDigitalOut leftWing (WING_LEFT);
	pros::ADIDigitalOut rightWing (WING_RIGHT);
	pros::ADIDigitalOut sideHang (SIDE_HANG);
	pros::ADIDigitalOut blocker (BLOCKER);
	pros::ADIDigitalOut barHang (BAR_HANG);
	
	
	// Joystick to read analog values for tank or arcade control.
	// Master controller by default.
	//initializes controller and pistons                                                                        
	Controller controller;
	
	 

	while (true) {
		double joysticMotion = controller.getAnalog(ControllerAnalog::leftY);
		if ((autoType == AUTONOMOUS_SKILLS)&&(selectedProgram==1)){
			double joysticMotion = -(controller.getAnalog(ControllerAnalog::leftY));
		}
		// Reads joystick input for left/right motion on the right stick
		double joysticTurning = controller.getAnalog(ControllerAnalog::rightX);
        // Calculate turning behavior using the regression model

       // Reads joystick input for up/down motion on the left stick
        

        // Calculate motor power using the regression model
		
       //Uses these new values to control the bot
        ///driveChassis->getModel()->arcade(joysticMotion, controller.getAnalog(ControllerAnalog::rightX));
		driveChassis->getModel()->arcade(joysticMotion,joysticTurning);

		//Initializes all the controller buttons
		ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton catapultButton(ControllerDigital::L2);
		ControllerButton catapultToggleOnButton(ControllerDigital::L2);
		ControllerButton catapultToggleOffButton(ControllerDigital::R2);
		ControllerButton shiftKeyButton(ControllerDigital::L1);
		ControllerButton wingOutLeftButton(ControllerDigital::left);
		ControllerButton wingInLeftButton(ControllerDigital::right);
		ControllerButton wingOutRightButton(ControllerDigital::A);
		ControllerButton wingInRightButton(ControllerDigital::Y);
		ControllerButton blockerUpButton(ControllerDigital::down);
		ControllerButton blockerDownButton(ControllerDigital::B);
		ControllerButton sideHangOutButton(ControllerDigital::up);
		ControllerButton sideHangInButton(ControllerDigital::X);
		ControllerButton barHangOutButton(ControllerDigital::down);
		ControllerButton barHangInButton(ControllerDigital::B);
	//pros::screen::set_pen(COLOR_BLUE);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	//pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());

		if (shiftKeyButton.isPressed()) {
			if (catapultToggleOnButton.isPressed()) {
			//Checks if the button for catapult progression is pressed, if so gives the catapultMotor 12000 mV
				catapultMotor.moveVoltage(11000);
				cataToggle=true;
			//if the catapult limit switch is pressed it stops the motor
			}
			else if (catapultToggleOffButton.isPressed()) {
			//Checks if the button for catapult progression is pressed, if so gives the catapultMotor 12000 mV
				catapultMotor.moveVoltage(0);
				cataToggle=false;
			//if the catapult limit switch is pressed it stops the motor
			}
			if (barHangOutButton.isPressed()) {
			if (barHangCheck==false){
				barHang.set_value(true);
				barHangCheck=true;
			}

		}	
		else if (barHangInButton.isPressed()) {
			if (barHangCheck){
				barHang.set_value(false);
				barHangCheck=false;
			}
		}
		}
		else{
		//Checks if the button for catapult is pressed
		if (catapultButton.isPressed()) {
			//Checks if the button for catapult progression is pressed, if so gives the catapultMotor 12000 mV
				catapultMotor.moveVoltage(11000);
			//if the catapult limit switch is pressed it stops the motor
		}
		 //else if the catapult back button it gives -12000 mV
		//else its stops powering the motor
		else{
			if(!cataToggle){
				catapultMotor.moveVoltage(0);
			}
		}
		//if the intakeIn button is pressed it gives the intake 12000 mV
		if (intakeInButton.isPressed()) {
        	intakeMotor.moveVoltage(12000);
    	} 
		//else if the intakeOut button is pressed it gives the intake -12000 mV
		else if (intakeOutButton.isPressed()) {
        	intakeMotor.moveVoltage(-12000);
		}
		//else it stops powering the intake motor
		else {
        	intakeMotor.moveVoltage(0);
    	}
		//If the wingOutButton is pressed and the wings aren't already out it extends 
		if (wingOutLeftButton.isPressed()) {
			if (wingCheckLeft==false){
				leftWing.set_value(true);
				wingCheckLeft=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (wingInLeftButton.isPressed()) {
			if (wingCheckLeft){
				leftWing.set_value(false);
				wingCheckLeft=false;
			}
		}
		if (wingOutRightButton.isPressed()) {
			if (wingCheckRight==false){
				rightWing.set_value(true);
				wingCheckRight=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (wingInRightButton.isPressed()) {
			if (wingCheckRight){
				rightWing.set_value(false);
				wingCheckRight=false;
			}
		}
		if (blockerDownButton.isPressed()) {
			if (blockerCheck==false){
				blocker.set_value(true);
				blockerCheck=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (blockerUpButton.isPressed()) {
			if (blockerCheck){
				blocker.set_value(false);
				blockerCheck=false;
			}
		}
		if (sideHangOutButton.isPressed()) {
			if (sideHangCheck==false){
				sideHang.set_value(true);
				sideHangCheck=true;
			}

		}	
		else if (sideHangInButton.isPressed()) {
			if (sideHangCheck){
				sideHang.set_value(false);
				sideHangCheck=false;
			}
		}
		}
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		
		pros::delay(10);
		
	}
	
}