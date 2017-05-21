#include "Arduino.h"
#include <esp32-hal-ledc.h>

#include "my_util.h"

int pwm1 = 34;
int pwm2 = 35;

int analogInputPin = 36;
int pwmLed = 5;

void setup()
{
	Serial.begin(115200);
	pinMode(pwm1, OUTPUT);
	pinMode(pwm2, OUTPUT);
	pinMode(pwmLed, OUTPUT);
	pinMode(analogInputPin, INPUT);

	ledcSetup(1, 50, 16); //Channel 1 at 50Hz with 16Bits depth
	ledcAttachPin(34, 1);
	ledcAttachPin(35, 1);
}

int writtenVal = 100;
int readedVal = 0;

void loop()
{
	if(Serial.available())
	{
		writtenVal = to_int(Serial.readString());
	}

	for (int i = 3300; i < 6500; i = i + 100)
	{
		ledcWrite(1, i);       // sweep the servo
		delay(100);
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
