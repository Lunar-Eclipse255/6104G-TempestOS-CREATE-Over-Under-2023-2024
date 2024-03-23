#include "main.h"
#include "display.hpp"
#include "autons.hpp"
#include "motors.h"
#include "gif-pros/gifclass.hpp"
#include "turn_voltage.hpp"
//defines adi ports for pistons
#define WING_LEFT_CURVED 'A'
#define WING_RIGHT_CURVED 'B'
#define WING_LEFT_DD 'C'
#define WING_RIGHT_DD 'D'
#define SIDE_HANG 'E'

//Declares variables for state checks.
bool wingCheckLeftCurved;
bool wingCheckRightCurved;
bool wingCheckLeftDD;
bool wingCheckRightDD;
bool sideHangCheck;
bool revUp;
bool flywheelIntake;
float error;
float prevError=0;
float integral=0;
float setpoint=600.0;
float derivative;
float power=120000;
float kP=3.1;
float kI=0;
float kD=0;
float k = 600.0/12000.0;
int value=0;

double motorVelocityCalc(double joystickInput) {
	//Coefficients for Cubic model
    double a = 5.0; 
    double b = 1.0; 
	double c = 2.0; 
	double d = 0.0; 
	double e = 0.0; 

    //motorVelocity = ax^4+ bx^3 + cx^2 + dx + e, where x is the joystick value: Quartic Linear regression model
    double motorVelocity = (a * pow(joystickInput, 4)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ 
	(d * joystickInput)+e;

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
    double turningValue = (a * pow(joystickInput, 3)) + (b * pow(joystickInput, 3)) + (c * pow(joystickInput, 2))+ 
	(d * joystickInput)+e;
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
pros::Rotation cataRotate(12);
Motor intakeMotor(-19);
Motor twoBarOneMotor (9);
Motor twoBarTwoMotor (-3);
Motor flywheelMotor (2);

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




//Runs initialization code. This occurs as soon as the program is started. All other competition modes are blocked by initialize; it is recommended to keep execution time for this mode under a few seconds.
void initialize() {
	//initializers the check varibles to false
	wingCheckLeftCurved=false;
	wingCheckRightCurved=false;
	wingCheckLeftDD=false;
	wingCheckRightDD=false;
	sideHangCheck = true;
	revUp=false;
	flywheelIntake=false;
	//pros::lcd::initialize();
	//initializes sylib
   	sylib::initialize();
	pros::ADIDigitalOut leftWingCurved (WING_LEFT_CURVED);
	pros::ADIDigitalOut rightWingCurved (WING_RIGHT_CURVED);
	pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
	pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);
	pros::ADIDigitalOut sideHang (SIDE_HANG);
	cataRotate.reset_position();
	pros::delay(200);
	sideHang.set_value(true);
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
	//runSelectedAuto();
	PIDScreen();
	//pSkills();
	rightRedOneAuton();
	//leftRedOneAuton();
	//elimMatchRightAuton();
	}
	
//Runs the operator control code. This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the operator control mode. If no competition control is connected, this function will run immediately following initialize(). If the robot is disabled or communications is lost, the operator control task will be stopped. Re-enabling the robot will restart the task, not resume it from where it left off.
void opcontrol() {
	twoBarOneMotor.moveVoltage(-12000);
	twoBarTwoMotor.moveVoltage(-12000);
	pros::delay(100);
	twoBarOneMotor.moveVoltage(0);
	twoBarTwoMotor.moveVoltage(0);
	
	if ((autoType == AUTONOMOUS_SKILLS)&&(selectedProgram==1)){
		dSkills();
	}
	
	driveChassis->setMaxVelocity(600);
	//clears screen
	//lv_init();
	//Testing: MainLVGL();
	//MainLVGL();
	pros::ADIDigitalOut leftWingCurved (WING_LEFT_CURVED);
	pros::ADIDigitalOut rightWingCurved (WING_RIGHT_CURVED);
	pros::ADIDigitalOut leftWingDD (WING_LEFT_DD);
	pros::ADIDigitalOut rightWingDD (WING_RIGHT_DD);
	pros::ADIDigitalOut sideHang (SIDE_HANG);
	sideHang.set_value(true);
	
	
	// Joystick to read analog values for tank or arcade control.
	// Master controller by default.
	//initializes controller and pistons                                                                        
	Controller controller;
	
	if (selectedDebugOption==1){ 
		PIDScreen();
	}
	while (true) {
		if (selectedDebugOption==1){ 
			PIDConstantUpdating();
		}
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
		ControllerButton wingOutLeftCurvedButton(ControllerDigital::right);
		ControllerButton wingInLeftCurvedButton(ControllerDigital::left);
		ControllerButton wingOutRightCurvedButton(ControllerDigital::Y);
		ControllerButton wingInRightCurvedButton(ControllerDigital::A);
		ControllerButton wingOutLeftDDButton(ControllerDigital::right);
		ControllerButton wingInLeftDDButton(ControllerDigital::left);
		ControllerButton wingOutRightDDButton(ControllerDigital::Y);
		ControllerButton wingInRightDDButton(ControllerDigital::A);
		ControllerButton sideHangOutButton(ControllerDigital::up);
		ControllerButton sideHangInButton(ControllerDigital::X);
		ControllerButton twoBarMatchLoadButton(ControllerDigital::down);
		ControllerButton twoBarResetButton(ControllerDigital::B);
		twoBarOneMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
		twoBarTwoMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
		flywheelMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
	//pros::screen::set_pen(COLOR_BLUE);
    //pros::screen::print(pros::E_TEXT_MEDIUM, 3, "%d",rightChassis.getActualVelocity());
	//pros::screen::print(pros::E_TEXT_MEDIUM, 3,"%d", leftChassis.getActualVelocity());

		
		//Checks if the button for catapult is pressed
		if (shiftKeyButton.isPressed()){
			if (armUpButton.isPressed()){
				twoBarOneMotor.moveVoltage(12000);
				twoBarTwoMotor.moveVoltage(12000);
			}
			else if (armDownButton.isPressed()){
				twoBarOneMotor.moveVoltage(-12000);
				twoBarTwoMotor.moveVoltage(-12000);
			}
			else {
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);

			}
			if (wingOutLeftDDButton.isPressed()) {
				if (wingCheckLeftDD==false){
					leftWingDD.set_value(true);
					wingCheckLeftDD=true;
				}
			}
			//Else if the wingOutButton is pressed and the wings aren't already in it extends 
			else if (wingInLeftDDButton.isPressed()) {
				if (wingCheckLeftDD){
					leftWingDD.set_value(false);
					wingCheckLeftDD=false;
				}
			}
			if (wingOutRightDDButton.isPressed()) {
				if (wingCheckRightDD==false){
					rightWingDD.set_value(true);
					wingCheckRightDD=true;
				}
			}
			//Else if the wingOutButton is pressed and the wings aren't already in it extends 
			else if (wingInRightDDButton.isPressed()) {
				if (wingCheckRightDD){
					rightWingDD.set_value(false);
					wingCheckRightDD=false;
				}
			}
		}
		else {
		//if the intakeIn button is pressed it gives the intake 12000 mV
		if (intakeInButton.isPressed()) {
			flywheelIntake=true;
        	intakeMotor.moveVoltage(12000);
    	} 
		//else if the intakeOut button is pressed it gives the intake -12000 mV
		else if (intakeOutButton.isPressed()) {
        	intakeMotor.moveVoltage(-12000);
		}
		//else it stops powering the intake motor
		else {
        	intakeMotor.moveVoltage(0);
				if (flywheelIntake){
					flywheelMotor.moveVoltage(0);
				}
			flywheelIntake=false;
    	}
		if (flywheelButton.isPressed()){
			if (!revUp){
				flywheelMotor.moveVoltage(12000);
				revUp=true;
				pros::delay(500);
			}
			flywheelMotor.moveVoltage(power);
			error = setpoint - (float) flywheelMotor.getActualVelocity();
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
			if(power>13000){
				power=13000;
			}
			printf("power: %f\n",power);

		}
		else {
			if (!flywheelIntake){
				flywheelMotor.moveVoltage(0);
				power=12000;
				revUp=false;
				integral=0;
			}
		}
		if (twoBarMatchLoadButton.isPressed()){
			if ((cataRotate.get_angle()/100)>350){
				cataRotate.reset_position();
				twoBarOneMotor.moveVoltage(-12000);
				twoBarTwoMotor.moveVoltage(-12000);
				pros::delay(100);
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
			}
			if((cataRotate.get_angle()/100)<130){
				while((cataRotate.get_angle()/100)<130){
					if (shiftKeyButton.isPressed()){
						if (armUpButton.isPressed()){
								break;
						}
					}
					printf("Rotation: %i\n",(cataRotate.get_angle()/100));
					twoBarOneMotor.moveVoltage(-12000);
					twoBarTwoMotor.moveVoltage(-12000);
				}
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
				
			}
			else if ((cataRotate.get_angle()/100)>131){
				while((cataRotate.get_angle()/100)>131){
					if (shiftKeyButton.isPressed()){
						if (armUpButton.isPressed()){
								break;
						}
					}
					twoBarOneMotor.moveVoltage(12000);
					twoBarTwoMotor.moveVoltage(12000);
				}
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
			}
			else {
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
			}
		}
		else if (twoBarResetButton.isPressed()){
			if ((cataRotate.get_angle()/100)>350){
				cataRotate.reset_position();
				twoBarOneMotor.moveVoltage(-12000);
				twoBarTwoMotor.moveVoltage(-12000);
				pros::delay(100);
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
			}
			if((cataRotate.get_angle()/100)<7){
				while((cataRotate.get_angle()/100)<8){
					if (shiftKeyButton.isPressed()){
						if (armUpButton.isPressed()){
								break;
						}
					}
					printf("Rotation: %i\n",(cataRotate.get_angle()/100));
					twoBarOneMotor.moveVoltage(-12000);
					twoBarTwoMotor.moveVoltage(-12000);
				}
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
				
			}
			else if ((cataRotate.get_angle()/100)>8){
				while((cataRotate.get_angle()/100)>8){
					if (shiftKeyButton.isPressed()){
						if (armUpButton.isPressed()){
								break;
						}
					}
					twoBarOneMotor.moveVoltage(12000);
					twoBarTwoMotor.moveVoltage(12000);
				}
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
			}
			else {
				twoBarOneMotor.moveVoltage(0);
				twoBarTwoMotor.moveVoltage(0);
			}
		}
		//If the wingOutButton is pressed and the wings aren't already out it extends 
		if (wingOutLeftCurvedButton.isPressed()) {
			if (wingCheckLeftCurved==false){
				leftWingCurved.set_value(true);
				wingCheckLeftCurved=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (wingInLeftCurvedButton.isPressed()) {
			if (wingCheckLeftCurved){
				leftWingCurved.set_value(false);
				wingCheckLeftCurved=false;
			}
		}
		if (wingOutRightCurvedButton.isPressed()) {
			if (wingCheckRightCurved==false){
				rightWingCurved.set_value(true);
				wingCheckRightCurved=true;
			}
		}
		//Else if the wingOutButton is pressed and the wings aren't already in it extends 
		else if (wingInRightCurvedButton.isPressed()) {
			if (wingCheckRightCurved){
				rightWingCurved.set_value(false);
				wingCheckRightCurved=false;
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