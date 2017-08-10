/*
 Dual Stepper Motor Control (Arduino UNO R3)
 Controls the speed and direction of two stepper motors
 via two analog inputs. Used to achieve two-dimensional
 movement controlled by a joystick. End-of-track sensors
 prevent damage to the structure and motors.
 Based on "Speed Control" example of the Stepper lib.
 Please note the Stepper library produces a bipolar sequence.
 By swapping the two middle cables, a unipolar seq. is obtained.
 By Eduardo Rivas, David Escobar y Ángel Moreno
 for Universidad Don Bosco of El Salvador, 2013.
 */

#include "Stepper.h"

// Set steps per revolution
const int PPR = 200;

// Motor Y in pins 10-13
Stepper motor1(PPR, 10, 11, 12, 13);
// Motor X in pins 6-9
Stepper motor2(PPR, 6, 7, 8, 9);

void setup()
{
	// Pins 2-5 set up as inputs with pullup resistors. Sensors are active-low.
	for (int i = 2; i <= 5; i++)
	{
		pinMode(i, INPUT_PULLUP);
	}
}

void loop()
{
	// MOTOR 1 CONTROL
	int speed = 0;
	int direction = 1;
	// Get joystick position on A1
	int position = analogRead(1);

	/*
	 Values between 562 and 1023 mean forward movement. Speed gets
	 mapped from 0 to 10 and direction stays positive. Sensors will
	 block any movement if HIGH.
	 */
	if (position > 562 and digitalRead(2) == HIGH)
	{
		speed = map(position, 562, 1023, 0, 10);
	}
	/*
	 Values between 0 and 462 mean backwards movement. Speed gets
	 mapped from 10 to 0 and direction is negative. Sensors will
	 block any movement if HIGH.
	 */
	if (position < 462 and digitalRead(3) == HIGH)
	{
		speed = map(position, 0, 462, 10, 0);
		direction = -1;
	}
	// Values between 462 and 562 mean no movement (joystick center zone)
	if (speed > 0)
	{
		motor1.setSpeed(speed);
		motor1.step(direction);
	}

	// MOTOR 2 CONTROL
	speed = 0;
	direction = 1;
	position = analogRead(2);

	if (position > 562 and digitalRead(4) == HIGH)
	{
		speed = map(position, 562, 1023, 0, 10);
	}

	if (position < 462 and digitalRead(5) == HIGH)
	{
		speed = map(position, 0, 462, 10, 0);
		direction = -1;
	}

	if (speed > 0)
	{
		motor2.setSpeed(speed);
		motor2.step(direction);
	}
}
