  /*************************/
 /* ARM CONTROL FUNCTIONS */
/*************************/

float jointAngles[] = {0, 0};      // Elbow, Wrist Angles(respectively)

int normalizeServos(float i) {
	/**	Takes an integer from 0 to 360, and
		normalizes it to a scale from 0 to 255.
		*/

	float value = i;
	float ratio = value / 180;

	int result = 255 * ratio;

	return result;
}

void setAngles() {
	writeDebugStreamLine("%i", jointAngles[0]);

	int elbowAngle = normalizeServos(jointAngles[0]);
	int wristAngle = normalizeServos(jointAngles[1]);

	servo[elbow1] = elbowAngle;
	servo[elbow2] = 255 - elbowAngle;
	servo[wrist] = wristAngle;
}

//void IKsolver(int x, int y) {
//	/**	*** 2-Dimensional Inverse-Kinematics Solver ***
//  *
//	  *  Solves (very) simple 2D Inverse Kinematics problems.
//	  *	 (Wikipedia "Inverse Kinematics" if you don't know what that is.
//	  *	  	http://en.wikipedia.org/wiki/Inverse_kinematics)
//	  *
//	  *	 Takes a target X and Y coordinate in front of the robot,
//	  *	 and calculates the angles that would result in a desired
//	  *	 configuration for each joint (Shoulder and Elbow) such that
//	  *	 the wrist of the robot is placed at those coordinates.
//	  *
//	  *	 The results are dumped into the JOINT_ANGLES array.
//	  */

//	/* Lengths of the arm segments (also act as the radii of circles in IK calculation). */
//	float r1 = ARM_SEGMENT_LEN_1;
//	float r2 = ARM_SEGMENT_LEN_2;

//	/* Distance between the two circles */
//	float d = sqrt(pow(x, 2) + pow(y, 2));

//	/* Use Heron's Formula and Triangle Area Formula to find half the length of the Common Chord. */
//	float s = (r1 + r2 + d) / 2.0;
//	float halfChord = sqrt(s * (s - r1) * (s - r2) * (s - d)) / d;

//	/* The Intersect Point is where the Common Chord and the distance line meet.
//	    Find the coordinates of the Intersect Point via Similar Triangles w/ the distance between the circles.
//	*/
//	float intersectLen = sqrt(pow(r1, 2) - pow(halfChord, 2));
//	float intersectX = (intersectLen * x) / d;
//	float intersectY = sqrt(pow(intersectLen, 2) - pow(intersectX, 2));

//	/* The elbow coordinate offsets from the Intersect Point form a similar triangle to the one formed by the
//	    X and Y distances between the two circles; Use this to find the offsets.
//	*/
//	float offsetX = (intersectLen * y) / x;
//	float offsetY = sqrt(pow(intersectLen, 2) - pow(offsetX , 2));

//	/* Find the coordinates of the "elbow" joint. */
//	float elbowX = intersectX - offsetX;
//	float elbowY = intersectY - offsetY;

//	/* Find the angle of the "shoulder" joint. */
//	float shoulderAngle = asin(elbowY / r1);

//	/* Find the angle of the "elbow" joint. */
//	float angleElbowToTarget = abs(atan((y - elbowY) / (x - elbowX)));
//	float elbowAngle = ((PI / 2) - shoulderAngle) - angleElbowToTarget;

//	/* Find the angle of the "wrist" joint. */
//	float wristAngle = (PI / 2) + angleElbowToTarget;

//	/* Normalize from Radians to 0-255 Servo Scale */
//	int shoulder = normalizeServos(shoulderAngle);
//	int elbow = normalizeServos(elbowAngle);
//	int wrist = normalizeServos(wristAngle);

//	/* Dump the results to the Array */
//	jointAngles[0] = shoulder;
//	jointAngles[1] = elbow;
//	jointAngles[2] = wrist;
//}

void moveShoulder(int mag) {
	/** Moves the Shoulder
		*/

	motor[motorArm] = mag * motorReduceRatio;
}

void initServos() {
	jointAngles[0] = 180;
	jointAngles[1] = 180;
	setAngles();
}

void unfold() {
	jointAngles[0] = 0;
	jointAngles[1] = 90;
	setAngles();
}

void straighten() {
	jointAngles[0] = 90;
	jointAngles[1] = 0;
	setAngles();
}

void manual(int joint, float mag) {
	/**	Takes an integer from 0 to 2, and
		moves the corresponding joints.

		0 = shoulder
		1 = elbow
		2 = wrist

		*/

	writeDebugStreamLine("Servo Ratio: %f", servoReduceRatio);
	writeDebugStreamLine("Motor Ratio: %f", motorReduceRatio);

	switch(joint) {
		case 0:
			moveShoulder(-mag);
			break;
		case 1:
			mag *= servoReduceRatio;
			if (jointAngles[0] + mag <= 180 && jointAngles[0] + mag >= 0)
				jointAngles[0] += mag;

			writeDebugStreamLine("%i", armBalanced);
			if (armBalanced) jointAngles[1] -= mag;

			break;
		case 2:
			mag *= servoReduceRatio;
			if (jointAngles[1] + mag <= 180 && jointAngles[1] + mag >= 0)
				jointAngles[1] += mag;
			break;
	}

	setAngles();
}
