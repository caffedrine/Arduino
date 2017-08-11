/**
 * Assuming that stepper drivers like DRV8843 are used and microsteps and enable pin are active.
 * So only pins required are STEP and possibly DIR
 */

#include "Arduino.h"

#include "../libs/my_util.h"

#define STEP1	9
#define STEP2	10

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");
	Serial.println(("Data format: speed1,speed2. e.g.: 200,200"));
}

int t1 = 200; bool lastState1 = false;
int t2 = 200; bool lastState2 = false;

String serialString;

void loop()
{
	/**
	 * Attempting to read serial without any loop delay in order
	 * to receive smooth speed changing
	 */
	if (Serial.available())
	{
		char c = Serial.read();

		if(c == '>')
		{
			// parsing recvString
			int speed1 = to_int(getStringPartByNr(serialString, ',', 0));
			int speed2 = to_int(getStringPartByNr(serialString, ',', 1));

			// print recv values as debugging data
			Serial.println("RECEIVED: " + to_string(speed1) + "," + to_string(speed2));

			// transfer vars to globals
			t1 = speed1;
			t2 = speed2;

			// reset serial string
			serialString = "";
		}
		else
		{
			serialString += c;
		}
	}

	// Update motor1 if is the time
	static unsigned long lastMicros1 = micros();
	if(micros() - lastMicros1 > (unsigned long)t1)
	{
		lastMicros1 = micros();
		lastState1 = !lastState1;

		// write digital signal
		digitalWrite(STEP1, lastState1);



	}

	// update motor2 if is the time
	static unsigned long lastMicros2 = micros();
	if(micros() - lastMicros2 > (unsigned long)t2)
	{
		lastMicros2 = micros();
		lastState2 = !lastState2;

		// write digital signal
		digitalWrite(STEP2, lastState2);
	}
}
