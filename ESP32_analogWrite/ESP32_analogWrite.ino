#include "Arduino.h"

#include <esp32-hal-ledc.h>
#include "my_util.h"

int pwm1 = 25;
int pwm2 = 26;

int analogInputPin = 36;

int pwmLed = 5;

void setup()
{
	Serial.begin(115200);
	pinMode(pwm1, OUTPUT);
	pinMode(pwm2, OUTPUT);
	pinMode(pwmLed, OUTPUT);
	pinMode(analogInputPin, INPUT);
}

int writtenVal = 100;
int readedVal = 0;

void loop()
{
	if(Serial.available())
	{
		writtenVal = to_int(Serial.readString());
	}




	//We want to make sure about value we write, so we read the value using another port
	//readedVal = map(analogRead(analogInputPin), 0, 4095, 0, 255);

	//Print data for debugging
	printPeriodicData("Current speed: " + to_string(writtenVal) + "\t Readed val: " + readedVal, 1000);
}

void updateMotor(int speed)
{
	static int interval = 15;
	static int last = 1;

	static long previousMillis = 0;
	if (millis() - previousMillis > interval)
	{
		previousMillis = millis();
		if(last == 0)
		{
			digitalWrite(25, HIGH);
			last = 1;
		}
		else
		{
			digitalWrite(25, LOW);
			last = 0;
		}
	}
}
