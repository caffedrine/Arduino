#include <Arduino.h>
#include <GpioBase.h>
#include <BasicLCD.h>
#include <LED.h>

using namespace Drivers;

GpioBase led(13, OUTPUT);
BasicLCD lcd(22, 23, 24, 25, 26, 27);


void setup()
{
	Serial.begin(115200);

	/* Set initial states */
	lcd.Init(16,  2);
}

static unsigned long PrevMillis = 0;
int i = 0;

void loop()
{
	if( millis() - PrevMillis >= 500 )
	{
		PrevMillis = millis();

		lcd.PrintLine(" " + String(++i), 0);
		lcd.PrintLine(" " + String(i*2), 1);

		led.Toggle();
	}

	Task_UpdateDisplay();
}

void Task_UpdateDisplay()
{
	static unsigned long PrevMillis = 0;

	/* Refresh display every 50 ms */
	if( millis() - PrevMillis >= 25)
	{
		PrevMillis = millis();
		lcd.Update();
	}
}
