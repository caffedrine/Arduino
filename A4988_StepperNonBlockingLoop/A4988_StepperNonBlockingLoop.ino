/*     Simple Stepper Motor Control
 *	   -- NON-BLOCKING LOOP --
 */

#include <Arduino.h>
#include "../libs/my_util.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
#define ENBL 13

// microsteps pins
#define MS1 10
#define MS2 11
#define MS3 12

void setup()
{
	//Start serial comm
	Serial.begin(115200);

	// Sets the two pins as Outputs
	pinMode(DIR, OUTPUT);
	pinMode(STEP, OUTPUT);
	pinMode(ENBL, OUTPUT);
	pinMode(MS1, OUTPUT);
	pinMode(MS2, OUTPUT);
	pinMode(MS3, OUTPUT);

	//predefine direction
	digitalWrite(DIR, HIGH); // Enables the motor to move in a particular direction

	//enable microsteping 16
	digitalWrite(MS1, HIGH);
	digitalWrite(MS2, HIGH);
	digitalWrite(MS3, HIGH);
}

unsigned int pause = 100;	//microseconds
void loop()
{

	/*
	// Makes 200 pulses*microsteps for making one full cycle rotation
	for (int x = 0; x < 200*16; x++)
	{
		digitalWrite(STEP, HIGH);
		delayMicroseconds(pause);
		digitalWrite(STEP, LOW);
		delayMicroseconds(pause);
	}
	delay(1000); // One second delay;
	//*/

	if(Serial.available())
	{
		int readVal = to_int ( Serial.readString() );
		if(readVal == 0)
		{
			pause = 200;
			digitalWrite(ENBL, HIGH);
			Serial.println("BRAKE!");
		}
		else
		{
			pause = readVal;
			digitalWrite(ENBL, LOW);
			Serial.println("NEW SPEED: " + to_string(pause));
		}
	}

	//Update motor every interval of time
	static unsigned int prevMicros = 0;
	static bool lastState = 0;
	if(micros() - prevMicros > pause)
	{
		digitalWrite(STEP, !lastState);

		lastState = !lastState;
		prevMicros = micros();
	}
	//*/
}
