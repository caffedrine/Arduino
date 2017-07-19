#include <Arduino.h>
#include <Wire.h>

#include "../libs/my_util.h"

int LED = 13;
int x = 0;

void setup()
{
	pinMode(LED, OUTPUT);

	// Start the I2C Bus as Slave on address 9 and setup callback function
	Wire.begin(9);
	Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes)
{
	x = Wire.read();    // read one character from the I2C
}
void loop()
{
	//If value received is 0 blink LED for 200 ms
	if (x == '0')
	{
		digitalWrite(LED, HIGH);
		delay(200);
		digitalWrite(LED, LOW);
		delay(200);
	}
	//If value received is 3 blink LED for 400 ms
	if (x == '3')
	{
		digitalWrite(LED, HIGH);
		delay(400);
		digitalWrite(LED, LOW);
		delay(400);
	}
}
