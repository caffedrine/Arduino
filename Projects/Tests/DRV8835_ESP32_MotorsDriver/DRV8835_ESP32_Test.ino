#include "Arduino.h"

#include "DRV8835_ESP32_MotorsDriver.h"
#include "my_util.h"

DRV8835 motors;

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");

	//Initialize motors
	motors.attachM1Pin(25, 26);	// IN=25, PH=26
	motors.attachM2Pin(27, 14);	// IN=27, PH=14 PS: Avoid pins 32-36 as those are INPUT only;
	motors.init();				//Make sure you run init(), otherwise it won't work

}

int writtenVal = 0;

void loop()
{
	if(Serial.available())
		writtenVal = to_int(Serial.readString());

	//Input values are from -4095 to 4095. Negative values mean backward
	motors.setM1Speed(writtenVal);
	motors.setM2Speed(writtenVal);

	//Print data for debugging
	printPeriodicData("Current speed: " + to_string(writtenVal), 1000);
}

