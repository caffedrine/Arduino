#include <Arduino.h>
#include "QRE1113_Driver.h"

QRE1113 encoder(35);

void setup()
{
	Serial.begin(115200);
	Serial.println("QRE1113 Reflectation Sensors");
	Serial.println("------------------------");
}


void loop()
{
	//Updating sensors data
	encoder.update();
	if(encoder.lastSteps != encoder.currSteps)
	{
		Serial.println("Steps: " + String(encoder.getSteps()));
	}
}

