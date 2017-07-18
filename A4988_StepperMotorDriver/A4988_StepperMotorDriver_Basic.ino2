/*     Simple Stepper Motor Control Exaple Code
 *
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *
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
}

int pause = 800;

void loop()
{
	digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
	// Makes 200 pulses for making one full cycle rotation
	for (int x = 0; x < 200; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(pause);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(pause);
	}
	delay(1000); // One second delay

	digitalWrite(dirPin, LOW); //Changes the rotations direction
	// Makes 400 pulses for making two full cycle rotation
	for (int x = 0; x < 400; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(pause);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(pause);
	}
	delay(1000);
}
