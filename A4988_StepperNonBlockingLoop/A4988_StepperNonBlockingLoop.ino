/*     Simple Stepper Motor Control
 *	   -- NON-BLOCKING LOOP --
 */

#include <Arduino.h>
#include "my_util.h"
#include "PWM.h"
#include "StepperPWM.h"

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
#define ENBL 13

// microsteps pins
#define MS1 10
#define MS2 11
#define MS3 12

StepperPWM stepper(DIR, STEP, ENBL, MS1, MS2, MS3);

void setup()
{
	//Start serial communication
	Serial.begin(115200);
	Serial.println("---START---");

	//Init motor
	if(stepper.init())
	{
		Serial.println("Motor initialized!");
		stepper.brake();
	}
	else
		Serial.println("ERROR: Can't initialize motor with given pins!");
}

unsigned long speed = 200;	//microseconds
void loop()
{
	if(Serial.available())
	{
		int readVal = to_int ( Serial.readString() );
		if(readVal == 0)
		{
			speed = 200;
			stepper.brake();
			Serial.println("BRAKE!");
		}
		else
		{
			speed = readVal;
			stepper.setFrequency(speed);
			stepper.run();	//Write val right away ^_^
			Serial.println("NEW SPEED: " + to_string(speed));
		}
	}
	stepper.run();
}
