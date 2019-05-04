#include <Arduino.h>
#include <GpioBase.h>
#include <BasicLCD.h>
#include <LED.h>
#include <Printf.h>
#include <StringUtil.h>

using namespace Drivers;
using namespace StringUtil;

GpioBase led(13, OUTPUT);
BasicLCD lcd(22, 23, 24, 25, 26, 27);

void setup()
{
	Serial.begin(115200);

	/* Set initial states */
	lcd.Init(16, 2);
}

static unsigned long PrevMillis = 0;
int i = 0;

void loop()
{
//	if( millis() - PrevMillis >= 500 )
//	{
//		PrevMillis = millis();
//
//		lcd.PrintLine(" " + String(++i), 0);
//		lcd.PrintLine(" " + String(i*2), 1);
//	}
//
//	Task_UpdateDisplay();

	fprintf(Serial, "int=%d padint=%05d\r\n", 123, 123);
	fprintf(Serial, "long=%l padlong=%08l\r\n", 123567, 1234567);
	fprintf(Serial, "str=%s substr=%*s\r\n\r\n", "abcde", 2, "abcde");

	delay(1000);
}

void Task_UpdateDisplay()
{
	static unsigned long PrevMillis = 0;

	/* Refresh display every 50 ms */
	if( millis() - PrevMillis >= 25 )
	{
		PrevMillis = millis();
		lcd.Update();
	}
}
