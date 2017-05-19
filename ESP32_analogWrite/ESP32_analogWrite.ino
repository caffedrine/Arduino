#include "Arduino.h"

#include <esp32-hal-dac.h>
#include "my_util.h"

int dac1Pin = 25;
int dac2Pin = 26;

int analogInputPin = 36;

void setup()
{
	Serial.begin(115200);
	pinMode(dac1Pin, OUTPUT);
	pinMode(dac2Pin, OUTPUT);
	pinMode(analogInputPin, INPUT);
}

int writtenVal = 0;
int readedVal = 0;

void loop()
{
	if(Serial.available())
	{
		writtenVal = to_int(Serial.readString());
	}

	dacWrite(25, writtenVal);//pin, 8bit value
	dacWrite(26, writtenVal);//pin, 8bit value
	delay(1);

	//We want to make sure about value we write, so we read the value using another port
	readedVal = analogRead(analogInputPin);
	delay(1);

	//Print data for debugging
	printPeriodicData("Current speed: " + to_string(writtenVal) + "\t Readed val: " + readedVal, 1000);
}
