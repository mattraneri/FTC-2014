  /*************************/
 /* PLOW CONTROL FUNCTIONS */
/*************************/
#include "globals.c"
bool isPlowOpen = false;
bool isGrabbing = false;

task PlowClose {
	servo[leftPlow] = 209;
	wait1Msec(1000);
	servo[rightPlow] = 0;
}

task PlowOpen {
	servo[rightPlow] = 255;
	wait1Msec(1000);
	servo[leftPlow] = 0;
}

void moveRight(int val) {
	servo[rightPlow] = val;
	//writeDebugStreamLine("Right: %i", servo[rightPlow]);
}

void moveLeft(int val) {
	servo[leftPlow] = val;
	//writeDebugStreamLine("Left: %i", servo[leftPlow]);
}

void togglePlow() {
	writeDebugStreamLine("Toggle plow");
	if(isPlowOpen) {
		StartTask(PlowOpen);
		isPlowOpen = false;
	} else {
		StartTask(PlowClose);
		isPlowOpen = true;
	}
}

void toggleGrab() {
	if(!isPlowOpen) {
		return;
	}

	writeDebugStreamLine("Toggle Grab");

	if(isGrabbing) {
		servo[rightPlow] = 0;
		servo[leftPlow] = 255;
		isGrabbing = false;
	} else {
		servo[rightPlow] = 100;
		servo[leftPlow] = 165;
		isGrabbing = true;
	}
}

void joy2Dpad() {
	switch(joystick.joy2_TopHat) {
		case 0:
			motor[motorArm] = -50;
			break;
		case 2:
			servo[basket] += 2;
			motor[motorArm] = 0;
			break;
		case 4:
			motor[motorArm] = 50;
			break;
		case 6:
			servo[basket] -= 2;
			motor[motorArm] = 0;
			break;
		case -1:
			motor[motorArm] = 0;
			break;
	}
}
