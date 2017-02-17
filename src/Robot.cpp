//#include <Joystick.h>
//#include <SampleRobot.h>
#include "WPILib.h"
#include "c:\Users\eeuser\wpilib\user\cpp\include\CANTalon.h"
//#include "CANTalon.h"
//#include "AHRS.h"
//#include <SmartDashboard/SendableChooser.h>
#include "SmartDashboard/SmartDashboard.h"


/**
 * This sample program shows how to control a motor using a joystick. In the operator
 * control part of the program, the joystick is read and the value is written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as range from
 * -1 to 1 making it easy to work together. The program also delays a short time in the loop
 * to allow other threads to run. This is generally a good idea, especially since the joystick
 * values are only transmitted from the Driver Station once every 20ms.
 */

class Robot : public frc::SampleRobot
{
	// The motor to control with the Joystick.
	// This uses a Talon speed controller; use the Victor or Jaguar classes for
	//   other speed controllers.
//	CANTalon* right_motor;
//	CANTalon* left_motor
	Joystick* right_stick; //Logitech Joystick
	Joystick* left_stick;
//	LiveWindow *lw = LiveWindow::GetInstance();
	CANTalon* LeftRearBaseMotor; //Talon 1 in CAN Bus
		CANTalon* LeftFrontBaseMotor; //Talon 2 in CAN Bus
		CANTalon* RightRearBaseMotor; //Talon 3 in CAN Bus
		CANTalon* RightFrontBaseMotor; //Talon 4 in CAN Bus

	//update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;
	const float KLeftMaster = 1; //KLeftMaster = Master Talon for left side
		const float KRightMaster = 3; //KRightMaster = Master Talon for right side

		const float KDeadZoneLimit = 0.1;
public:

	 void OperatorControl()
	 {
//		test_motor = new CANTalon(9)
		 left_stick = new Joystick(1);
		right_stick = new Joystick(0);
//		lw->AddSensor("Robot", "CANTalon", test_motor);
//		lw->Run();
//
		 	RightFrontBaseMotor = new CANTalon(KRightMaster); //RightFrontBase is the master Talon for the right side
			RightFrontBaseMotor->SetSafetyEnabled(true);

			RightRearBaseMotor = new CANTalon(2);
			RightRearBaseMotor->SetControlMode(CANTalon::kFollower); //RightRearBase is the follower to RightRearBase
			RightRearBaseMotor->Set(KRightMaster);

			//Sets up Left motors
			//Left base motors are inverted
			LeftFrontBaseMotor = new CANTalon(KLeftMaster); //LeftFrontBase is the master Talon on the Left side
			LeftFrontBaseMotor->SetSafetyEnabled(true);
			LeftFrontBaseMotor->SetInverted(true);

			LeftRearBaseMotor = new CANTalon(4);
			LeftRearBaseMotor->SetControlMode(CANTalon::kFollower); //LeftRearBase is the follower to the LeftRearBase
			LeftRearBaseMotor->Set(KLeftMaster);
			LeftRearBaseMotor->SetInverted(true);

			while(IsOperatorControl() && IsEnabled())
			{
				RightFrontBaseMotor->Set(right_stick->GetY());
				LeftFrontBaseMotor->Set(left_stick->GetY());
			}
		}

	};

/*motor->Reset();
		RightFrontBaseMotor->Reset();
		float encoder = LeftFrontBaseMotor->GetEncPosition();
		float encoder2 = RightFrontBaseMotor->GetEncPosition();
		float distance = 10;
		while(encoder < distance && encoder2 < distance)
		{
			RightFrontBaseMotor->Set(.25);
			LeftFrontBaseMotor->Set(.25);
			encoder = LeftFrontBaseMotor->GetEncPosition();
			encoder2 = RightFrontBaseMotor->GetEncPosition();
		}*/
START_ROBOT_CLASS(Robot)
