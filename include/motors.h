#include "main.h"
//declares the motors, chassis, and ADIButton
extern Motor backLeftDriveMotor;
extern Motor middleLeftDriveMotor;
extern Motor frontLeftDriveMotor;
extern Motor backRightDriveMotor;
extern Motor middleRightDriveMotor;
extern Motor frontRightDriveMotor;
extern Motor upRightDriveMotor;
extern Motor upLeftDriveMotor;
extern MotorGroup leftChassis;
extern MotorGroup rightChassis;
extern Motor intakeMotor;
extern Motor catapultMotor;
extern ADIButton catapultLimit;
extern std::shared_ptr<ChassisController> driveChassis;