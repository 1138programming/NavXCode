#include "WPILib.h"
//#include "c:\Users\eeuser\wpilib\user\cpp\include\CANTalon.h"
#include "CANTalon.h"
#include "AHRS.h"
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

/**
 * This sample program shows how to control a motor using a joystick. In the operator
 * control part of the program, the joystick is read and the value is written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as range from
 * -1 to 1 making it easy to work together. The program also delays a short time in the loop
 * to allow other threads to run. This is generally a good idea, especially since the joystick
 * values are only transmitted from the Driver Station once every 20ms.
 */
class Robot : public SampleRobot
{
	// The motor to control with the Joystick.
	// This uses a Talon speed controller; use the Victor or Jaguar classes for
	//   other speed controllers.
	CANTalon* motor_rear_left;
//	CANTalon* motor_front_left;
	CANTalon* motor_rear_right;
//	CANTalon* motor_front_right;
	Joystick* l_stick; //Logitech Joystick
	Joystick* r_stick; //XBox Joystick
	AHRS *ahrs;
	LiveWindow *lw = LiveWindow::GetInstance();


	//update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;

public:

	/**
	 * Runs the motor from the output of a Joystick.
	 */
	void OperatorControl() {
		l_stick = new Joystick(1); // Initialize Joystick on port 1.
		r_stick = new Joystick(2); // Initialize Joystick on port 2.

		ahrs = new AHRS(SPI::Port::kMXP);
		//ahrs->ZeroYaw();
		lw->AddSensor("Robot", "9AxisGyro", ahrs);

		//Left side motors
		motor_rear_left = new CANTalon(2);
	//	motor_front_left = new CANTalon(4);
		//The front motor is reversed
//		motor_front_left->SetInverted(true);
		//The rear motor is following the front motor
	//	motor_rear_left->SetControlMode(CANTalon::kFollower);
	//	motor_rear_left->Set(2);

		//Right side motors
		motor_rear_right = new CANTalon(1);
	//	motor_front_right = new CANTalon(3);
		//The front motor is reversed
	//	motor_front_right->SetInverted(true);
		//The rear motor is following the front motor
	//	motor_rear_right->SetControlMode(CANTalon::kFollower);
	//	motor_rear_right->Set(1);

		//12bit encoder, 4096 ticks per rotation
//		motor_front.SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
//		motor_front.SetSensorDirection(true); /* keep sensor and motor in phase */
//		motor_front.SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
//		motor_front.SetSensorDirection(true); /* keep sensor and motor in phase */
		while (IsOperatorControl() && IsEnabled()) {
			// Set the motor controller's output.
			// This takes a number from -1 (100% speed in reverse) to +1 (100% speed forwards).
			//motor_rear_left->Set(r_stick->GetY());
			//motor_rear_right->Set(r_stick->GetY());
			lw->Run();

			if(ahrs->GetYaw() < 15 && ahrs->GetYaw() > -15)
				motor_rear_right->Set(0.2);
			else
				motor_rear_right->Set(0);
			Wait(kUpdatePeriod); // Wait 5ms for the next update.
		}
	}
};

START_ROBOT_CLASS(Robot)
