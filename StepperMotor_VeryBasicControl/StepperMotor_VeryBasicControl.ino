#include <Arduino.h>

#define DIR 	13
#define STEP	10

void setup()
{
	Serial.begin(115200);
	Serial.println("---START---");

	pinMode(DIR, OUTPUT);
	pinMode(STEP, OUTPUT);


	pinMode(2, INPUT);
	pinMode(3, INPUT);
	//pinMode(4, INPUT);
	pinMode(5, INPUT);
	pinMode(6, INPUT);
	pinMode(7, INPUT);

	pinMode(9, INPUT);
}


int pause = 800;
void loop()
{
		digitalWrite(STEP, HIGH);
		delayMicroseconds(pause);
		digitalWrite(STEP, LOW);
		delayMicroseconds(pause);
}
