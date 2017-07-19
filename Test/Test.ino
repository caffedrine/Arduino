#include <Arduino.h>

void setup()
{
	//Start serial comm
	Serial.begin(115200);
	Serial.println("---START---");

	pinMode(A0, INPUT);
	pinMode(10, OUTPUT);
}

void loop()
{
	analogWrite(10, 812);
	Serial.println( analogRead(A0) );
	delay(300);
}
