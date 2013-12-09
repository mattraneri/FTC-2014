  /*************************/
 /* PLOW CONTROL FUNCTIONS */
/*************************/
#include "globals.c"
bool isPlowOpen = false;

task PlowClose {
	servo[leftPlow] = 255;
	wait1Msec(1000);
	servo[rightPlow] = 0;
}

task PlowOpen {
	servo[rightPlow] = 255;
	wait1Msec(1000);
	servo[leftPlow] = 0;
}

void moveRight(int val) {
	servo[rightPlow] += val;
}

void moveLeft(int val) {
	servo[leftPlow] += val;
}

void togglePlow() {
	writeDebugStreamLine("Toggle pressed");
	if(isPlowOpen) {
		StartTask(PlowOpen);
		isPlowOpen = false;
	} else {
		StartTask(PlowClose);
		isPlowOpen = true;
	}
}
