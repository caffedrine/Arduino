/**
 * Assuming that stepper drivers like DRV8843 are used and microsteps and enable pin are active.
 * So only pins required are STEP and possibly DIR
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
}

void loop()
{
	if (Serial.available())
	{
		String recvStr = Serial.readString();

		// parsing recvString
		int speed1 = to_int(getStringPartByNr(recvStr, ',', 0));
		int speed2 = to_int(getStringPartByNr(recvStr, ',', 1));

		// setting up motors speeds
		motor1.setFrequency(speed1);
		motor2.setFrequency(speed2);

		// sending PWM output
		motor1.run();
		motor2.run();
	}
}
