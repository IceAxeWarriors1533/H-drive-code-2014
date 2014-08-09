#pragma config(Motor,  port1,           rightDrive,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightClawPivot,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftClawPivot,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightArmPivot,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftArmPivot,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightRackLift, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftRackLift,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           middleDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          leftDrive,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Platform config
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(OFF) //OFF or Competition
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

// One joystick tank drive control. Also called arcade drive
void tank_drive(float x, float y)
{
    //Reset to zero
    motor[right] = 0;
    motor[left] = 0;
	if(abs(x) > 5 || abs(y) > 5)
	{
        //Movement
		motor[right] = (x - y) / 2;
		motor[left] = (x + y) / 2;
	}
}

//Two joystick h-drive control
void h_drive(float xLeftStick, float yLeftStick, float xRightStick, float yRightStick)
{
    //Reset to zero
    motor[right] = 0;
    motor[left] = 0;
    motor[middle] = 0;
    if(abs(xRightStick) > 5 || abs(yRightStick) > 5 || abs(xLeftStick) > 5 || abs(yLeftStick) > 5)
    {
        //Directional Movement
        motor[right] += yRightStick;
        motor[left] += yRightStick;
        motor[middle] += xRightStick;
        //Turning
        motor[right] += xLeftStick;
		motor[left] += -xLeftStick;
    }
}

// Lift for the claw arm
void drive_rack_lift(int speed)
{
		motor[rightRackLift] = speed;
		motor[leftRackLift] = -speed;
}

// Drive the lift down
void rack_lift_down()
{
	drive_rack_lift(-127);
}

// Drive the lift up
void rack_lift_up()
{
	drive_rack_lift(127);
}

// Stop the lift
void rack_lift_stop()
{
	drive_rack_lift(0);
}

void arm_pivot_drive(int speed)
{
	motor[rightArmPivot] = speed;
	motor[leftArmPivot] = speed;
}

void arm_pivot_up()
{
	arm_pivot_drive(64);
}

void arm_pivot_down()
{
	arm_pivot_drive(-64);
}

void arm_pivot_stop()
{
	arm_pivot_drive(0);
}

void claw_drive(int speed)
{
	motor[claw] = speed;
}

void claw_open()
{
	claw_drive(64);
}

void claw_close()
{
	claw_drive(-64);
}

void claw_stop()
{
	claw_drive(0);
}

void claw_pivot_up()
{
	motor[rightClawPivot] = 60;
	motor[leftClawPivot] = 60;
}

void claw_pivot_down()
{
	motor[rightClawPivot] = -60;
	motor[leftClawPivot] = -60;	
}

void claw_pivot_stop()
{
	motor[rightClawPivot] = 0;
	motor[leftClawPivot] = 0;	
}

// All init functions and definitions go in here
void pre_auton()
{
}

// All functions for fully autonomous control of robot go here
task autonomous()
{
	//AutonomousCodePlaceholderForTesting();
}

// All functions for joystick-operated mode go here
task usercontrol()
{
	while(true)
	{
		int xSpeed = vexRT[Ch2];
		int ySpeed = vexRT[Ch1];
		int midSpeed = vexRT[Ch4];

		bool bRackLiftDown = vexRT[Btn6D];
		bool bRackLiftUp = vexRT[Btn6U];

		bool bArmPivotUp = vexRT[Btn8U];
		bool bArmPivotDown = vexRT[Btn8D];

		bool bClawOpen = vexRT[Btn5D];
		bool bClawClose = vexRT[Btn5U];
		
		bool bClawPivotUp = vexRT[Btn7U];
		bool bClawPivotDown = vexRT[Btn7D];

		tank_drive(xSpeed, ySpeed);

		if(bRackLiftUp)
			rack_lift_up();
		else if(bRackLiftDown)
			rack_lift_down();
		else if(bArmPivotUp)
			arm_pivot_up();
		else if(bArmPivotDown)
			arm_pivot_down();
		else if(bClawOpen)
			claw_open();
		else if(bClawClose)
			claw_close();
		else if(bClawPivotUp)
			claw_pivot_up();
		else if(bClawPivotDown)
			claw_pivot_down();
			
		if(!bRackLiftUp && !bRackLiftDown)
			rack_lift_stop();
			
		if(!bArmPivotUp && !bArmPivotDown)
			arm_pivot_stop();
			
		if(!bClawOpen && !bClawClose)
			claw_stop();
			
		if(!bClawPivotUp && !bClawPivotDown)
			clawPivot_stop();

		motor[middle] = midSpeed;
	}
}
