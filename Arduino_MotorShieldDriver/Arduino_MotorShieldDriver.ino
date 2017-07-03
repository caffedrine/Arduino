#include "Arduino.h"

#include "DCMotor.h"
#include "my_util.h"

//Motors
DCMotor M1(3, 12);
DCMotor M2(11, 13);

void setup()
{
	//Start serial - we need to get speed
	Serial.begin(115200);
	Serial.println("---STARTED---");

	//Make sure motors are stopped
	M1.brake();
	M2.brake();

	//Set directions
	M1.setDirection(DCMotor::DIRECTION_FORWARD);
	M2.setDirection(DCMotor::DIRECTION_FORWARD);
}

int speed = 0;
void loop()
{
	//Run Forest, run!
	M1.run();
	M2.run();

	//Update motors speeds from serial
	if(Serial.available())
	{
		speed = to_int(Serial.readString());
		M1.setSpeed(speed);
		M2.setSpeed(speed);
	}

	//Print speed every 1 seconds
	printPeriodicData("Speed: " + to_string(speed), 1000);
}
