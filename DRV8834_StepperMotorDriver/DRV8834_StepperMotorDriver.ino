#include <Arduino.h>
#include "DRV8834.h"
#include "../libs/my_util.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

//enable pin
#define ENBL 13

// All the wires needed for full functionality
#define DIR 8
#define STEP 9

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
