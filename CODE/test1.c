#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     frontRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    arm,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "JoystickDriver.c"
void twoJoystickMovement(int totalLeft, int totalRight, int threshHold){
	if(joystick.joy1_y1 > threshHold || joystick.joy1_y1 < 0 - threshHold){
		int power = joystick.joy1_y1;
		totalRight += power;
	}
	if(joystick.joy1_y2 > threshHold || joystick.joy1_y2 < 0 - threshHold){
		int power = joystick.joy1_y2;
		totalLeft += power;
		//motor[frontLeft] = power;
		//totalRight -= power;
		//motor[frontRight] = -power;
	}
	motor[frontLeft] = totalLeft;//normalize(joystick.joy1_y1);
	motor[frontRight] = totalRight;//-normalize(joystick.joy1_y1);
}
void servoMovement(int threshHold){
	if(joy1Btn(1) == 1){
		servo[clamp] -= 1;
	}
	if(joy1Btn(2) == 1) {
		servo[clamp] += 1;
	}
	if(joy1Btn(7) == 1) {
		servo[arm] += 1;
	}
	if(joy1Btn(8) == 1){
		servo[arm] -= 1;
	}
}
void betterMovement(int threshHold){
	int totalLeft = 0, totalRight = 0;
	int power = joystick.joy1_y1;
	int turnPower = joystick.joy1_x2;
	if(joystick.joy1_y1 > threshHold){ //Move/Turn While moving forwards
		if(turnPower <= threshHold){
			totalRight = power + turnPower;
			totalLeft = power;
		}
		if(turnPower > threshHold){
			totalRight = power;
			totalLeft = power - turnPower;
		}
	}
	if(joystick.joy1_y1 < 0 - threshHold){ //Moving/Turn While moving backwards
		if(turnPower <= threshHold){
			totalLeft = power - turnPower;
			totalRight = power;
		}
		if(turnPower > threshHold){
			totalLeft = power;
			totalRight = power + turnPower;
		}
	}
	motor[frontLeft] = totalLeft;
	motor[frontRight] = totalRight;
}
task main()
{
	int threshHold = 15;
	while(true) {
		getJoystickSettings(joystick);
		//twoJoystickMovement(totalLeft, totalRight, threshHold);
		servoMovement(threshHold);
		betterMovement(threshHold);
	}
}
\