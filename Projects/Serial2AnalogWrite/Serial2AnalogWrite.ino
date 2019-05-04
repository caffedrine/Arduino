#include "Arduino.h"
#include "../libs/my_util.h"

// For analog write select an digital pin.
// Analog pins are only for analog inputs
#define PIN 8

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");
	Serial.println("Interval 10bits: 0-1023");

	pinMode(PIN, OUTPUT);
}

void loop()
{
	/*
	if(Serial.available())
	{
		int readVal = to_int ( Serial.readString() );
		analogWrite(PIN, readVal);
		Serial.println("Written on " + to_string(PIN) + " value: " + to_string(readVal));
	}
	*/

	//Or automatic fading
	int pause = 200; //ms
	for(int i=0; i <= 1023; i++)
	{
		analogWrite(PIN, i);
		Serial.println("Written on " + to_string(PIN) + " value: " + to_string(i));
		delay(pause);
	}
	for(int i=1022; i>=1; i++)
	{
		analogWrite(PIN, i);
		Serial.println("Written on " + to_string(PIN) + " value: " + to_string(i));
		delay(pause);
	}
}
