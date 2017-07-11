/*
 * Clock Microstepping demo
 *
 * Moves the stepper motor like the seconds hand of a watch.
 *
 * Copyright (C)2015 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "DRV8834.h"
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9

// 2-wire basic config, microstepping is hardwired on the driver
// BasicStepperDriver stepper(DIR, STEP);

// microstep control for DRV8834
#define M0 10
#define M1 11
DRV8834 stepper(MOTOR_STEPS, DIR, STEP, M0, M1);


void setup()
{
	/*
	 * Set target motor RPM=1 and microstepping=1
	 */
	stepper.begin(1, 1);
}

void loop()
{
	/*
	 * The easy way is just tell the motor to rotate 360 degrees at 1rpm
	 */
	stepper.rotate(360);
}
