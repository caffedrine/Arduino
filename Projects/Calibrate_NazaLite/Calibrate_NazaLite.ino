/**
 * BAsic Arduino program to calibrate DJI Naza Lite
*/

#include <Servo.h>

#include <string.h>

Servo AIL, ELE, THR, RUDD, U;
int AILpin = 8;
int ELEpin = 9;
int THRpin = 10;
int RUDDpin = 11;
int Upin = 12;

#define ESC_MIN 0
#define ESC_MAX 180

Servo motor;

void setup()
{

	Serial.begin(38400);
	Serial.println("Program begin...");
	Serial.println("This program will calibrate the ESC.");

	pinMode(AILpin, OUTPUT);
	pinMode(ELEpin, OUTPUT);
	pinMode(THRpin, OUTPUT);
	pinMode(RUDDpin, OUTPUT);
	pinMode(Upin, OUTPUT);

	AIL.attach(AILpin, ESC_MIN, ESC_MAX);
	ELE.attach(ELEpin, ESC_MIN, ESC_MAX);
	THR.attach(THRpin, ESC_MIN, ESC_MAX);
	RUDD.attach(RUDDpin, ESC_MIN, ESC_MAX);
	U.attach(Upin, ESC_MIN, ESC_MAX);

	armESC();
	delay(500);

	Serial.println("Now writing maximum output.");
	Serial.println("Turn on power source, then wait 2 seconds and press any key.");

	THR.write(ESC_MAX);
	AIL.write((ESC_MAX - ESC_MIN) / 2 + ESC_MIN);
	ELE.write((ESC_MAX - ESC_MIN) / 2 + ESC_MIN);
	RUDD.write((ESC_MAX - ESC_MIN) / 2 + ESC_MIN);
	U.write(map(52, 0, 100, ESC_MIN, ESC_MAX));

	while (!Serial.available());
	Serial.read();

	// Send min output
	Serial.println("Sending minimum output");
	THR.write(ESC_MIN);
	AIL.write((ESC_MAX - ESC_MIN) / 2 + ESC_MIN);
	ELE.write((ESC_MAX - ESC_MIN) / 2 + ESC_MIN);
	RUDD.write((ESC_MAX - ESC_MIN) / 2 + ESC_MIN);
	U.write(map(52, 0, 100, ESC_MIN, ESC_MAX));
}

String serialString = "";

void loop()
{
	while (Serial.available())
	{
		char c = Serial.read();  //gets one byte from serial buffer
		serialString += c; //makes the String readString
		delay(1);  //slow looping to allow buffer to fill with next character
	}

	if (serialString.length() > 0)
	{
		//motor.write(map(to_int(serialString), 0, 100, MIN_SIGNAL, MAX_SIGNAL));
		THR.write(map(to_int(serialString), 0, 100, ESC_MIN, ESC_MAX));
		serialString = "";
	}
}

int to_int(String str)
{
	return atoi(str.c_str());
}

void armESC()
{
	THR.write(ESC_MIN);
	RUDD.write(ESC_MAX);
	AIL.write(ESC_MIN);
	ELE.write(ESC_MIN);
	delay(1000);

	RUDD.write(ESC_MIN);
}

void disarmESC()
{
	THR.write(ESC_MIN);
	RUDD.write(ESC_MAX);
	AIL.write(ESC_MIN);
	ELE.write(ESC_MIN);
	delay(1000);

	RUDD.write(ESC_MIN);
}
