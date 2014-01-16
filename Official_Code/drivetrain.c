  /********************************/
 /* DRIVETRAIN CONTROL FUNCTIONS */
/********************************/

bool allStopped = true;				// Are all drivetrain motors stopped?
bool abCycleActive = false;			// Is Active Braking being applied to the motors right now?

// XY-Plane Movement Only
void move(int xMag, int yMag) {
	/**	Takes 2 normalized input integers from -100 to 100, and uses them to calculate the proper motor angles.

		See my sketchbook for the math. If there are any glaring errors, contact me (RLAM) immediately!
		*/

	// Joystick Magnitudes
	float jXMag = (float) xMag;
	float jYMag = (float) yMag;

	float mag = abs(sqrt(pow(xMag, 2) + pow(yMag, 2)));		// magnitude = positive sqrt(x^2 + y^2)

	/* Angles */

	// Joystick Angle
	float joyAngle = asin(jYMag / mag);

	if (jXMag <= 0 && jYMag >= 0) {			// QII
		//writeDebugStreamLine("QII");
		joyAngle = PI - joyAngle;
	}
	else if (jXMag <= 0 && jYMag <= 0) {	// QIII
		//writeDebugStreamLine("QIII");
		joyAngle = PI - joyAngle;
	}
	else if (jXMag >= 0 && jYMag <= 0) {	// QIV
		//writeDebugStreamLine("QIV");
		joyAngle = 2 * PI + joyAngle;
	}

	float motorAngle = joyAngle - (PI / 4);		// Motor Axes are offset by 45 degrees (or pi / 4 radians) from the Joystick Axes.

	//writeDebugStreamLine("Joy Angle: %f; Motor Angle: %f", joyAngle, motorAngle);

	// Motor Magnitudes
	float mXMag = mag * cos(motorAngle);
	float mYMag = mag * sin(motorAngle);

	// Run X-Axis Motors
	motor[motorFL] = mXMag;
	motor[motorBR] = mXMag;

	// Run Y-Axis Motors
	motor[motorFR] = mYMag;
	motor[motorBL] = mYMag;

	allStopped = false;
}

// Spin Only
void spin(int mag) {
	/** Takes a motor-normalized integer, and uses it for spin magnitude.
		*/

	// Spin!
	motor[motorFL] = mag;
	motor[motorBR] = -mag;
	motor[motorBL] = mag;
	motor[motorFR] = -mag;

	allStopped = false;
}

// Move AND Turn
void moveTurn(int moveMag, int turnMag) {
	/** Operates sort of like tank treads/differential steering!
		ie, if you want to turn right, slow down the right wheels, and vice versa.
		*/

	//writeDebugStreamLine("%i", moveMag);

	if (turnMag < 0) {
		motor[motorBL] = moveMag + turnMag;
		motor[motorBR] = moveMag;

		motor[motorFL] = moveMag + turnMag;
		motor[motorFR] = moveMag;

	}
	else if (turnMag > 0) {
		motor[motorBL] = moveMag;
		motor[motorBR] = moveMag - turnMag;

		motor[motorFL] = moveMag;
		motor[motorFR] = moveMag - turnMag;
	}

	allStopped = false;
}

// Stop!!!
void halt() {
	if (allStopped) return;		// No need to halt anything if it's already halted.

	if (!activeBraking) {
		// Stop all motors without Active Braking
		motor[motorFL] = MOTOR_OFF;
		motor[motorBR] = MOTOR_OFF;
		motor[motorBL] = MOTOR_OFF;
		motor[motorFR] = MOTOR_OFF;

		allStopped = true;
	}
	//else {
		//if (!abCycleActive) {
		//	// Reverse all motors to begin Active Braking Cycle.
		//	motor[motorFL] *= -1;
		//	motor[motorBR] *= -1;
		//	motor[motorBL] *= -1;
		//	motor[motorFR] *= -1;

		//	ClearTimer(T1);

		//	abCycleActive = true;
		//}
		//else {
		//	if (time1[T1] >= AB_MAX_TIME) {
		//		// Stop all motors when Active Braking Cycle is complete.
		//		motor[motorFL] = MOTOR_OFF;
		//		motor[motorBR] = MOTOR_OFF;
		//		motor[motorBL] = MOTOR_OFF;
		//		motor[motorFR] = MOTOR_OFF;

		//		allStopped = true;

		//		abCycleActive = false;
		//	}
		//}
	//}
}
