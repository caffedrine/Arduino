#include <Arduino.h>
#include <Stepper.h>

#include "../libs/my_util.h"

const int enablePin = 13;

const int stepsPerRevolution = 200; // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;  // number of steps the motor has taken

void setup()
{
	Serial.begin(9600);
	pinMode(enablePin, OUTPUT);
}

int speed = 0;

void loop()
{
	//Grab speed from serial port
	if(Serial.available())
	{
		speed = to_int(Serial.readString());
		if(speed == 0)
		{
			Serial.println("BRAKE");
			digitalWrite(enablePin, HIGH);
		}
		else
		{
			Serial.println("New speed: " + to_string(speed));
			digitalWrite(enablePin, LOW);
		}
	}
	if(speed > 0)
	{
		myStepper.setSpeed(speed);
		myStepper.step(stepsPerRevolution / 1);
	}
}


