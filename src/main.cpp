#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
//defines adi ports for pistons
#define WING_LEFT 'B'
#define WING_RIGHT 'C'
#define SIDE_HANG 'D'



double motorVelocityCalc(double joystickInput) {
	//Coefficients for Cubic model
    double a = 5.0; 
    double b = 1.0; 
	double c = 2.0; 
	double d = 0.0; 
	double e = 0.0; 

    //motorVelocity = ax^4+ bx^3 + cx^2 + dx + e, where x is the joystick value: Quartic Linear regression model
    double motorVelocity = (a * pow(joystickInput, 4)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ (d * joystickInput)+e;

    //Adjusts value to fit into expected input value 
    motorVelocity = std::min(100.0, std::max(-100.0, motorVelocity));

    //Adds the direction back to the motor power
	if (selectedProfile==0){
    return (joystickInput < 0) ? -motorVelocity : motorVelocity;
	}
	else {
		return (joystickInput < 0) ? motorVelocity : -motorVelocity;
	}

}

double turningValueCalc(double joystickInput) {
    //Coefficients for Quartic model
	
    double a = 4.0; 
    double b = 4.0; 
	double c = 1.0; 
	double d = 0.0; 
	double e = 0.0; 

    //motorVelocity = ax^4+ bx^3 + cx^2 + dx + e, where x is the joystick value: Quartic Linear regression model
    double turningValue = (a * pow(joystickInput, 3)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ (d * joystickInput)+e;
    //Adjusts value to fit into expected input value 
    turningValue = std::min(1.0, std::max(-1.0, turningValue));

	//returns the turningValue
	return turningValue;
}


//Initializes the drive motors to what port a motor is plugged into and if its reversed
Motor backLeftDriveMotor (-10);
Motor frontLeftDriveMotor (-20);
Motor backRightDriveMotor (1);
Motor frontRightDriveMotor (11);
auto cataDistance = DistanceSensor(12);

//Sets up which side of the bot motors are in.
MotorGroup leftChassis ({backLeftDriveMotor,frontLeftDriveMotor});
MotorGroup rightChassis ({backRightDriveMotor, frontRightDriveMotor});
std::shared_ptr<ChassisController> driveChassis =
	ChassisControllerBuilder()
		//.withMotors(leftChassis,rightChassis)
		//Sets which motors to use
		.withMotors(
			leftChassis,
			rightChassis
		)
		
		// Green cartridge, 3.25 in wheel diam, 17 in wheel track, 60:36 gear ratio.
		.withDimensions({AbstractMotor::gearset::blue, (60.0 / 36.0)}, {{3.25_in, 10.5_in}, imev5BlueTPR})
		//{0.002, 0.001, 0.0001}  
		
		
		
		.withLogger(
        	std::make_shared<Logger>(
            	TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
            	"/ser/sout", // Output to the PROS terminal
            	Logger::LogLevel::debug // Most verbose log level
        	)
		)
		.build();
//Initializes the drive chassis
//Initializes the subsytem motors as well as the Adi Button
Motor intakeMotor(-5);
Motor twoBarMotor (9);
Motor flywheelMotor (2);



//Declares variables for state checks.
bool wingCheckLeft;
bool sideHangCheck;
bool wingCheckRight;
bool revUp;
double error;
double prevError=0;
double integral=0;
int setpoint=200;
double derivative;
double power=0;
float kP=1.3;
float kI=0.5;
float kD=0.2;
double k = 200.0/12000.0;

//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//initializers the check varibles to false
	wingCheckLeft=false;
	wingCheckRight=false;
	sideHangCheck = false;
	revUp=false;
	//pros::lcd::initialize();
	//initializes sylib
   	sylib::initialize();
	pros::ADIDigitalOut leftWing (WING_LEFT);
	pros::ADIDigitalOut rightWing (WING_RIGHT);
	pros::ADIDigitalOut sideHang (SIDE_HANG);
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
	PIDScreen();
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
	
	
	// Joystick to read analog values for tank or arcade control.
	// Master controller by default.
	//initializes controller and pistons                                                                        
	Controller controller;
	
	 
	PIDScreen();
	while (true) {
		PIDConstantUpdating();
		double joysticMotion = controller.getAnalog(ControllerAnalog::leftY);
		// Reads joystick input for left/right motion on the right stick
		double joysticTurning = controller.getAnalog(ControllerAnalog::rightX);
        // Calculate turning behavior using the regression model
		//double turningValue = turningValueCalc(joysticTurning);

       // Reads joystick input for up/down motion on the left stick

        // Calculate motor power using the regression model
        //double motorVelocity = motorVelocityCalc(joysticMotion);
       // Reads joystick input for up/down motion on the left stick
        

        // Calculate motor power using the regression model
		
       //Uses these new values to control the bot
        ///driveChassis->getModel()->arcade(joysticMotion, controller.getAnalog(ControllerAnalog::rightX));
		driveChassis->getModel()->arcade(joysticMotion,joysticTurning);

		//Initializes all the controller buttons
		ControllerButton intakeOutButton(ControllerDigital::R2);
		ControllerButton intakeInButton(ControllerDigital::R1);
		ControllerButton flywheelButton(ControllerDigital::L2);
		ControllerButton armUpButton(ControllerDigital::R2);
		ControllerButton armDownButton(ControllerDigital::R1);
		ControllerButton shiftKeyButton(ControllerDigital::L1);
		ControllerButton wingOutLeftButton(ControllerDigital::left);
		ControllerButton wingInLeftButton(ControllerDigital::right);
		ControllerButton wingOutRightButton(ControllerDigital::A);
		ControllerButton wingInRightButton(ControllerDigital::Y);
		ControllerButton sideHangOutButton(ControllerDigital::up);
		ControllerButton sideHangInButton(ControllerDigital::X);
		flywheelMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
	//pros::screen::set_pen(COLOR_BLUE);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	//pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());

		
		//Checks if the button for catapult is pressed
		if (shiftKeyButton.isPressed()){
			//flywheelMotor.moveVoltage(12000);
			if (armUpButton.isPressed()){
				twoBarMotor.moveVoltage(12000);
			}
			else if (armDownButton.isPressed()){
				twoBarMotor.moveVoltage(-12000);
			}
			else {
				twoBarMotor.moveVoltage(0);
			}
		}
		else {
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
		if (flywheelButton.isPressed()){
			if (!revUp){
				flywheelMotor.moveVoltage(12000);
				revUp=true;
				pros::delay(500);
			}
			flywheelMotor.moveVoltage(power);
			error = setpoint - flywheelMotor.getActualVelocity();
			printf("Velocity: %f\n",flywheelMotor.getActualVelocity());
			printf("error: %f\n",error);
    		integral = integral + error;
			if (error==0){
				integral=0;
			}
			printf("Integral: %f\n",integral);
			derivative = error - prevError;
			printf("derivative: %f\n",derivative);
			prevError = error;
			power = (error*kP + integral*kI + derivative*kD)/k;
			printf("power: %f\n",power);
			pros::delay(15);

		}
		else {
			flywheelMotor.moveVoltage(0);
			power=12000;
			revUp=false;
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