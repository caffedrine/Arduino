/*     Simple Stepper Motor Control
 *	   -- NON-BLOCKING LOOP --
 */

#include <Arduino.h>
#include "../libs/my_util.h"
#include "PWM.h"

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
	//analogWrite(ENBL, LOW);
	pinMode(A0, INPUT);
	 //initialize all timers except for 0, to save time keeping functions
	 InitTimersSafe();
	 bool success = SetPinFrequencySafe(STEP, 2000);


	 if(success)
		 Serial.println("SUCCESS");
	 else
		 Serial.println("FAIL");

}

unsigned long pause = 200;	//microseconds
static unsigned long prevMicros = 0;
static bool lastState = 0;

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
			//pwmWrite(STEP, 1);
			Serial.println("BRAKE!");
		}
		else
		{
			pause = readVal;
			analogWrite(ENBL, LOW);
			//pwmWrite(STEP, 1);
			Serial.println("NEW SPEED: " + to_string(pause));
		}
	}

	pause = map(analogRead(A0), 0, 1024, 0, 5000);
	//Update motor every interval of time
	if(micros() - prevMicros > pause)
	{
		prevMicros = micros();
		lastState = !lastState;
		digitalWrite(STEP, lastState);
	}
	//*/
}
