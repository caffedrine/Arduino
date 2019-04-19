#include "Arduino.h"

#include "GpioBase.h"
#include "HC595.h"

using namespace Drivers;

GpioBase led(13, OUTPUT);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	led.Toggle();
	delay(500);
}
