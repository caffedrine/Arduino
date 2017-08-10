/**
 * Assuming that stepper drivers like DRV8843 are used and microsteps and enable pin are active.
 * So only pins required are STEP and possibly DIR
 *
 * LSTER: There is aproblem to be solved...
 * frequency is set for both pins the same even if try to set different...need to be investigated
 */

#include "Arduino.h"

#include "../libs/my_util.h"
#include "StepperPWM.h"

#define STEP1	9
#define STEP2	10

// defining motors = PARAMS: directionPIN, stepPIN, enablePIN
StepperPWM motor1(0, STEP1, 0);
StepperPWM motor2(0, STEP2, 0);

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");
	Serial.println(("Data format: speed1,speed2. e.g.: 200,200"));

	// Check if pins can be used to change PWM freq
	if (!motor1.init() || !motor2.init())
	{
		Serial.println("ERROR: Can't initialize motors pins! Use pins 9 and 10 instead.");
		while (1)
			;
	}
}

void loop()
{
	if (Serial.available())
	{
		String recvStr = Serial.readString();

		// parsing recvString
		int speed1 = to_int(getStringPartByNr(recvStr, ',', 0));
		int speed2 = to_int(getStringPartByNr(recvStr, ',', 1));

		// print recv values as debugging data
		Serial.println("RECEIVED: " + to_string(speed1) + "," + to_string(speed2));

		// setting up motors speeds
		if(!motor1.setFrequency(speed1)) Serial.println("MOTOR 1 PWN FREQ SET FAILED!!");
		if(!motor2.setFrequency(speed2)) Serial.println("MOTOR 2 PWN FREQ SET FAILED!!");

		// sending PWM output
		motor1.run();
		motor2.run();
	}
}
