/*     Simple Stepper Motor Control
 *	   -- NON-BLOCKING LOOP --
 */

#include <Arduino.h>

// defines pins numbers
const int dirPin = 8;
const int stepPin = 9;

void setup()
{
	// Sets the two pins as Outputs
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	//predefine direction
	digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
}

int pause = 800;	//vaqry speed from here
void loop()
{

	// Makes 200 pulses for making one full cycle rotation
	for (int x = 0; x < 200; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(pause);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(pause);
	}
	delay(1000); // One second delay;
}
