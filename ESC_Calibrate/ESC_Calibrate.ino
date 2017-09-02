#include <Servo.h>

#include <string.h>

#define MAX_SIGNAL 180
#define MIN_SIGNAL 0
#define MOTOR_PIN 8

Servo motor;

void setup() 
{
	
	Serial.begin(9600);
	Serial.println("Program begin...");
	Serial.println("This program will calibrate the ESC.");

	motor.attach(MOTOR_PIN, MIN_SIGNAL, MAX_SIGNAL);
	
	Serial.println("Now writing maximum output.");
	Serial.println("Turn on power source, then wait 2 seconds and press any key.");
	motor.write(MAX_SIGNAL);

	// Wait for input
	while (!Serial.available());
	Serial.read();

	// Send min output
	Serial.println("Sending minimum output");
	motor.write(MIN_SIGNAL);
	/**/
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