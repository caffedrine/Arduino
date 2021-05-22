#include <Servo.h>

#include <string.h>

#define MAX_SIGNAL 180
#define MIN_SIGNAL 0
#define MOTOR_PIN 8

Servo motor;

void setup()
{

	Serial.begin(9600);
	motor.attach(MOTOR_PIN, MIN_SIGNAL, MAX_SIGNAL);
}

String serialString = "";
void loop()
{
	while (Serial.available())
	{
		char c = Serial.read();  //gets one byte from serial buffer
		serialString += c; //makes the String readString
		delay(2);  //slow looping to allow buffer to fill with next character
	}

	if (serialString.length() > 0)
	{
		//motor.write(map(to_int(serialString), 0, 100, MIN_SIGNAL, MAX_SIGNAL));
		motor.write(map(to_int(serialString), 0, 100, MIN_SIGNAL, MAX_SIGNAL));
		serialString = "";
	}
}

int to_int(String str)
{
	return atoi(str.c_str());
}
