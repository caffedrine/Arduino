#include "Arduino.h"
#include "../libs/my_util.h"

#define PIN A1

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");
	Serial.println("Interval 10bits: 0-1023");

	pinMode(PIN, OUTPUT);
}

void loop()
{

	if(Serial.available())
	{
		int readVal = to_int ( Serial.readString() );
		analogWrite(PIN, readVal);
		Serial.println("Written on " + to_string(PIN) + " value: " + to_string(readVal));
	}
}
