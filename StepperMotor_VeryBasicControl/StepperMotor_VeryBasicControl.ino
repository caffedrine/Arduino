#include <Arduino.h>

#define DIR 	8
#define STEP	9

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");

	pinMode(DIR, OUTPUT);
	pinMode(STEP, OUTPUT);
}


int pause = 800;
void loop()
{
		digitalWrite(STEP, HIGH);
		delayMicroseconds(pause);
		digitalWrite(STEP, LOW);
		delayMicroseconds(pause);
}
