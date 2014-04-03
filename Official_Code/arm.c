  /*************************/
 /* PLOW CONTROL FUNCTIONS */
/*************************/
#include "globals.c"

void moveRight(int val) {
	servo[rightPlow] = val;
	//writeDebugStreamLine("Right: %i", servo[rightPlow]);
}

void moveLeft(int val) {
	servo[leftPlow] = val;
	//writeDebugStreamLine("Left: %i", servo[leftPlow]);
}

void joy2Dpad() {
	switch(joystick.joy2_TopHat) {
		case 0:
			motor[motorArm] = -50;
			break;
		case 4:
			motor[motorArm] = 50;
			break;
		case -1:
			motor[motorArm] = 0;
			//motor[motorPlat] = 0;
			break;
	}
}
