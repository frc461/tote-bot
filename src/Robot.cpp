#include "WPILib.h"

#define DRIVER_CONTROL_PORT 0
#define OPERATOR_CONTROL_PORT 1

#define LEFT_DRIVE_MOTOR_PWM 0
#define RIGHT_DRIVE_MOTOR_PWM 1
#define LEFT_LIFT_MOTOR_PWM 2
#define RIGHT_LIFT_MOTOR_PWM 3
#define LEFT_INTAKE_MOTOR_PWM 4
#define RIGHT_INTAKE_MOTOR_PWM 5

#define LEFT_LIFT_ENCODER 8
#define RIGHT_LIFT_ENCODER 9

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	RobotDrive myRobot;
	Joystick driverStick;
	Joystick operatorStick;

	Jaguar leftDrive;
	Jaguar rightDrive;
	Jaguar leftLift;
	Jaguar rightLift;
	Jaguar leftIntake;
	Jaguar rightIntake;

public:
	Robot() :
			myRobot(0, 1),	// these must be initialized in the same order
			driverStick(DRIVER_CONTROL_PORT),		// as they are declared above.
			operatorStick(OPERATOR_CONTROL_PORT),
			leftDrive(LEFT_DRIVE_MOTOR_PWM),
			rightDrive(RIGHT_DRIVE_MOTOR_PWM),
			leftLift(LEFT_LIFT_MOTOR_PWM),
			rightLift(RIGHT_LIFT_MOTOR_PWM),
			leftIntake(LEFT_INTAKE_MOTOR_PWM),
			rightIntake(RIGHT_INTAKE_MOTOR_PWM)
	{
		myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			leftIntake.Set(0.8);
			rightIntake.Set(0.8);

			leftLift.Set(operatorStick.GetRawAxis(1));
			rightLift.Set(operatorStick.GetRawAxis(1));

			myRobot.TankDrive(driverStick.GetRawAxis(5), driverStick.GetRawAxis(1), true); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
