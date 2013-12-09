  /******************************/
 /* CONTROLLER INPUT FUNCTIONS */
/******************************/

#include "drivetrain.c"
#include "arm.c"



int normalizeJoysticks(int i) {
	/**	Takes an integer from JOY_THRESHOLD to 128, and
		normalizes it to a scale from MOTOR_OFF to MOTOR_MAX.
		*/

	if (abs(i) < JOY_THRESHOLD) return 0;						// Anything below the joystick threshold is considered to be zero.

	float value = (float) i;
	float ratio = (abs(value) - JOY_THRESHOLD) / (JOY_MAX - JOY_THRESHOLD);

	if (i < -JOY_THRESHOLD) ratio *= -1;

	return MOTOR_MAX * ratio;									// For everything else, normalize.
}

void readJoys1() {
	/**	Reads the Joysticks on Controller 1 (NOT the buttons!), then acts accordingly.
		*/

	int joy1x = joystick.joy1_x1;
	int joy1y = joystick.joy1_y1;

	int joy2x = joystick.joy1_x2;
	int joy2y = joystick.joy1_y2;


	// Check Joystick Input States
	/*
		0: No movement
		1: XY-Plane movement only (Joy1 Only)
		2: Spin only (Joy2 Only)
		3: Movement AND Turning (Joy1 AND Joy2)
	*/

	bool joy1Active = abs(joy1x) > JOY_THRESHOLD || abs(joy1y) > JOY_THRESHOLD;
	bool joy2Active = abs(joy2x) > JOY_THRESHOLD;

	int joyState = 0;

	if (joy1Active && !joy2Active) joyState = 1;
	else if (!joy1Active && joy2Active) joyState = 2;
	else if (joy1Active && joy2Active) joyState = 3;
	else joyState = 0;

	joy1x = normalizeJoysticks(joy1x);
	joy1y = normalizeJoysticks(joy1y);

	joy2x = normalizeJoysticks(joy2x);
	joy2y = normalizeJoysticks(joy2y);

	//writeDebugStreamLine("joy1x: %i", joy1x);
	//writeDebugStreamLine("joy1y: %i", joy1y);
	//writeDebugStreamLine("joy2x: %i", joy2x);
	//writeDebugStreamLine("joy2y: %i", joy2y);

	//if (joy1x == 0) player1Strafing = false;

	switch (joyState) {
		case 1:
			//writeDebugStreamLine("State 1: XY-Plane Movement Only");
			move(joy1x, joy1y);
			//if (joy1x > 0) player1Strafing = true;
			break;
		case 2:
			//writeDebugStreamLine("State 2: Spin Only");
			spin(joy2x);
			break;
		case 3:
			//writeDebugStreamLine("State 3: Movement AND Turning");
			moveTurn(joy1y, joy2x);
			break;
		default:
			//writeDebugStreamLine("State 0: HALT!");
			halt();
			break;
	}
}

void readJoys2() {
	/**	Reads the Joysticks on Controller 2 (NOT the buttons!), then acts accordingly.
		*/

	int joy1x = joystick.joy2_x1;
	int joy1y = joystick.joy2_y1;

	int joy2x = joystick.joy2_x2;
	int joy2y = joystick.joy2_y2;

	if(joy1x > JOY_THRESHOLD) {
		moveLeft(-1);
	} else if(joy1x < -JOY_THRESHOLD) {
		moveLeft(1);
	}

	if(joy2x > JOY_THRESHOLD) {
		moveRight(-1);
	} else if(joy2x < -JOY_THRESHOLD) {
		moveRight(1);
	}
}

void readButtons1() {
	/**	Reads the Buttons on Controller 1 (NOT the Joysticks!), then acts accordingly.
		*/
	if (joy1Btn(6)) {
		motor[motorPlat] = MOTOR_PLAT;
	}
	else if (joy1Btn(5)) {
		motor[motorPlat] = -MOTOR_PLAT;
	}
	else {
		motor[motorPlat] = MOTOR_OFF;
	}
}
bool wasPressed = false;
bool lastPressed = false;
void readButtons2() {
	/**	Reads the Buttons on Controller 2 (NOT the Joysticks!), then acts accordingly.
		*/
	if (joy2Btn(4) && wasPressed == false) {
		togglePlow();
		wasPressed = true;
	}
	if(lastPressed = true && joy2Btn(4) == false) {
		wasPressed = false;
	}
	lastPressed = joy2Btn(4);
	//writeDebugStreamLine("Ratio: %f", motorReduceRatio);

}
