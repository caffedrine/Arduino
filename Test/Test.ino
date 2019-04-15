#include <Arduino.h>

#define PULSE_PIN 	13
#define START_MOVE	12

#define DELAY_US	500

void setup()
{
	Serial.begin(9600);
	pinMode(PULSE_PIN, OUTPUT);
	pinMode(START_MOVE, INPUT);
}

int CurrTimestamp, PrevTimestamp;

int StepsToDo = 0;
bool ToggleFlag;

void loop()
{
	if(Serial.available() > 0)
	{
		StepsToDo = Serial.parseInt();
		Serial.println(StepsToDo);
	}

	if(StepsToDo > 0)
	{
		digitalWrite(PULSE_PIN, HIGH);
		delayMicroseconds(DELAY_US);
		digitalWrite(PULSE_PIN, LOW);
		delayMicroseconds(DELAY_US);

		StepsToDo--;
	}
	else if(StepsToDo == -1)
	{
		digitalWrite(PULSE_PIN, HIGH);
		delayMicroseconds(DELAY_US/2);
		digitalWrite(PULSE_PIN, LOW);
		delayMicroseconds(DELAY_US);

		if(digitalRead(START_MOVE) == LOW)
			StepsToDo = 0;
	}
	else
	{
		if(digitalRead(START_MOVE) == HIGH)
			StepsToDo = -1;
	}
}
