/**
	DRV8834 Steper Motor - Driver Library
	Source: https://github.com/laurb9/StepperDriver/blob/master/examples/ClockStepper/ClockStepper.ino
*/
#include "DRV8834.h"

//Pins definitions
#define MOTOR_STEPS	200// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define	DIR		8	//direction pin
#define	STEP	9	//step pin
#define MS1		10	//microstep
#define MS2		11	//microstep
#define MS3		0	//microstep

DRV8834 motor(MOTOR_STEPS, DIR, STEP);

void setup()
{
	Serial.begin(115200);
	Serial.println("---SRART---");

	motor.setRPM(1);
	// Set full speed mode (microstepping also works for smoother hand movement
	motor.setMicrostep(1);
}

void loop()
{
	motor.rotate(360);
}
