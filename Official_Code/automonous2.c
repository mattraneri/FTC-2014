#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     irSensor,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S3,     touchSensor,    sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorPlat,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorArm,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    rightPlow,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    leftPlow,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    basket,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

#include "globals.c"
#include "JoystickDriver.c"  				//Include file to "handle" the Bluetooth messages.
void initializeRobot()
{
	// Place code here to initialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	//initServos();
	return;
}

void rightPark() {
	motor[motorFL] = 100;
	motor[motorFR] = 100;
	motor[motorBL] = 100;
	motor[motorBR] = 100;
	wait1Msec(1100);
	motor[motorFL] = 00;
	motor[motorFR] = 00;
	motor[motorBL] = 00;
	motor[motorBR] = 00;
	wait1Msec(1000);
	motor[motorFL] = 100;
	motor[motorFR] = -100;
	motor[motorBL] = 100;
	motor[motorBR] = -100;
	wait1Msec(350);
	motor[motorFL] = 00;
	motor[motorFR] = 00;
	motor[motorBL] = 00;
	motor[motorBR] = 00;
	wait1Msec(1000);
	motor[motorFL] = 100;
	motor[motorFR] = 100;
	motor[motorBL] = 100;
	motor[motorBR] = 100;
	wait1Msec(1300);
	motor[motorFL] = 00;
	motor[motorFR] = 00;
	motor[motorBL] = 00;
	motor[motorBR] = 00;
}

void leftPark() {
	motor[motorFL] = 100;
	motor[motorFR] = 100;
	motor[motorBL] = 100;
	motor[motorBR] = 100;
	wait1Msec(1100);
	motor[motorFL] = 00;
	motor[motorFR] = 00;
	motor[motorBL] = 00;
	motor[motorBR] = 00;
	wait1Msec(1000);
	motor[motorFL] = -100;
	motor[motorFR] = 100;
	motor[motorBL] = -100;
	motor[motorBR] = 100;
	wait1Msec(350);
	motor[motorFL] = 00;
	motor[motorFR] = 00;
	motor[motorBL] = 00;
	motor[motorBR] = 00;
	wait1Msec(1000);
	motor[motorFL] = 100;
	motor[motorFR] = 100;
	motor[motorBL] = 100;
	motor[motorBR] = 100;
	wait1Msec(1300);
	motor[motorFL] = 00;
	motor[motorFR] = 00;
	motor[motorBL] = 00;
	motor[motorBR] = 00;
}

void parkOnRamp(int state) {
	switch(state) {
		case 0:
			rightPark();
			break;
		case 1:
			leftPark();
			break;
	}
}
task main()
 {
  initializeRobot();

  waitForStart();
 	parkOnRamp(1);
  //Autonomous code goes here.
 }

