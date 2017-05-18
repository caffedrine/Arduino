#include <Arduino.h>

#include "my_util.h"

int encoderLeftPin = 35;
int encoderRightPin = 39;

int leftVal  = 0, lastLeftVal   = 0, leftSteps  = 0;
int rightVal = 0, lastRightVal  = 0, rightSteps = 0;

//Prototypes
void printPeriodicData(String, int);

void setup()
{
	pinMode(encoderLeftPin, INPUT);
	pinMode(encoderRightPin, INPUT);
	Serial.begin(115200);
	Serial.println("QRE1113 Reflectation Sensors");
	Serial.println("------------------------");
}

void loop()
{
	lastLeftVal  = leftVal;
	lastRightVal = rightVal;

	leftVal  = analogRead(encoderLeftPin);
	rightVal = analogRead(encoderRightPin);

	if(leftVal < 500)
		leftVal = 1;
	else if(leftVal > 2150)
		leftVal = 0;
	else
		leftVal = lastLeftVal;

	if(rightVal < 500)
		rightVal = 1;
	else if(rightVal > 2150)
		rightVal = 0;
	else
		rightVal = lastRightVal;

	if(lastLeftVal != leftVal)
		leftSteps += leftVal;

	if(lastRightVal != rightVal)
		rightSteps += rightVal;

	printPeriodicData("Steps:   " + to_string(leftSteps) + "\t" + to_string(rightSteps), 10);/*
	printPeriodicData("Steps:   " + to_string(leftVal) + "\t" + to_string(rightVal), 100);//*/
}

void printPeriodicData(String data, int interval = 1000)
{
	static long previousMillis = 0;
	if (millis() - previousMillis > interval)
	{
		previousMillis = millis();
		Serial.println(data);
	}
}
