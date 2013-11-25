  /******************************************/
 /* PROGRAM GLOBAL VARIABLES AND CONSTANTS */
/******************************************/


/* Constants */

const int JOY_MAX = 128;					// Maximum possible Joystick input
const int JOY_THRESHOLD = 10;				// Program will ignore Joystick input that is less than this value.

const int MOTOR_MAX = 100;					// Motor Max Value
const int MOTOR_OFF = 0;					// Motor Stop Value

const float SERVO_RATIO_INCREMENT = 0.005;	// Servo ratio increment
const float MOTOR_RATIO_INCREMENT = 0.05;		// Motor ratio increment

const int MOTOR_PLAT = 50;		// Platform Speed

//const float ARM_SEGMENT_LEN_1 = 8.25;		// Length of Arm Segments (TODO: inches? cm? Probably cm because of smaller graduations)
//const float ARM_SEGMENT_LEN_2 = 12.75;

//const int AB_MAX_TIME = 250;					// How long the Active Braking cycle should last, in milliseconds

const float TOPHAT_INCREMENT = 80.0;			// How much the TopHat increments by, per cycle.

/* Variables */

bool robotActive = false;					// Is the robot "active" and allowed to execute actions? (Hard-coded safety system)
bool activeBraking = false;					// Should Active Braking be used when halting the motors?

bool armBalanced = true;

float motorReduceRatio = 0.5;		// Motor reduction ratio
float servoReduceRatio = 0.005;		// Servo reduction ratio

//bool player1Strafing = false;			// Is Player 1 currently strafing the robot?
