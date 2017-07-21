#include <Arduino.h>

void setup()
{
	//Start serial comm
	Serial.begin(115200);
	Serial.println("---START---");

	pinMode(A0, INPUT);
	pinMode(10, OUTPUT);
}

long i = 0;
void loop()
{
	Serial.println(i++);
	delay(500);
}
