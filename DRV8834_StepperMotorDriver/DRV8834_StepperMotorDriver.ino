<<<<<<< HEAD
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
=======
/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
//#define ENBL 7

// Since microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, ENBL);

void setup()
{
	/*
	 * Set target motor RPM.
	 * These motors can do up to about 200rpm.
	 * Too high will result in a high pitched whine and the motor does not move.
	 *
	 * Also tell the driver the microstep level we selected.
	 * If mismatched, the motor will move at a different RPM than chosen.
	 */
	stepper.begin(120, MICROSTEPS);
>>>>>>> origin/master
}

void loop()
{
<<<<<<< HEAD
	motor.rotate(360);
=======

	// energize coils - the motor will hold position
	// stepper.enable();

	/*
	 * Moving motor one full revolution using the degree notation
	 */
	stepper.rotate(360);

	/*
	 * Moving motor to original position using steps
	 */
	stepper.move(-200 * MICROSTEPS);

	// pause and allow the motor to be moved by hand
	// stepper.disable();

	delay(5000);
>>>>>>> origin/master
}
