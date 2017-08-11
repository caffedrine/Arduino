#include <Arduino.h>

#include "DRV8834.h"
#include "../libs/my_util.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200

// All the wires needed for full functionality
#define DIR 	4
#define STEP 	9
#define ENBL 	8

#define M0 		11
#define M1 		12


//DRV8834 stepper(MOTOR_STEPS, DIR, STEP, ENBL);
DRV8834 stepper(MOTOR_STEPS, DIR, STEP, ENBL, M0, M1);	//microsteps enabled
DRV8834 stepper1(200, 2, 10, 8, M0, M1);


void setup()
{
	Serial.begin(115200);
	Serial.println("---STARTED---");
	stepper.begin(300, 1);

	pinMode(3, INPUT);
	pinMode(5, INPUT);
	pinMode(6, INPUT);
	pinMode(7, INPUT);

	pinMode(9, INPUT);

}

int speed = 200;
void loop()
{

	//Grab speed from serial port
	if(Serial.available())
	{
		speed = to_int(Serial.readString());
		if(speed == 0)
		{
			Serial.println("BRAKE");
			stepper.disable();
			//digitalWrite(ENBL, LOW);
		}
		else
		{
			Serial.println("New speed: " + to_string(speed));
			stepper.setRPM(speed);

			stepper1.setRPM(speed-200);

			stepper.enable();
			//digitalWrite(ENBL, HIGH);
		}
	}
	stepper.move(1);
	stepper1.move(1);
}



