/*     Simple Stepper Motor Control Exaple Code
 *
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *
 */

#include <Arduino.h>
#include "A4988.h"
#include "../libs/my_util.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
#define ENBL 13

// microstep control for A4988
#define MS1 10
#define MS2 11
#define MS3 12
A4988 stepper(MOTOR_STEPS, DIR, STEP, ENBL, MS1, MS2, MS3);

void setup()
{
	Serial.begin(115200);

	//Pass RPM and MICROSTEPS
	stepper.begin(50, 16);
}

void loop()
{
	if(Serial.available())
	{
		int readVal = to_int(Serial.readString());

		if(readVal == 0)
		{
			stepper.setRPM(0);
			stepper.disable();
			Serial.println("BRAKE");
		}
		else
		{
			stepper.setRPM(readVal);
			stepper.enable();
			Serial.println("SPEED: " + to_string(readVal));
		}
	}
	stepper.move(1);

	//Time required for one microstep
//	int micros1 = micros();
//	stepper.move(1);
//	int micros2 = micros();
//	Serial.println("Time for one step: " + to_string(micros2-micros1));
//	delay(500);
}
