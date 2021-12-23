#include "Arduino.h"
#include <LedMatrixDriver.h>
#include <LED.h>
#include <Printf.h>
#include <SerialAsync.h>

#define HC595_DEBUG_MESSAGES	1
#define HC595_DEBUG_ENABLED		1


#define PIN_REG_DATA	5u
#define PIN_REG_CLK		3u
#define PIN_REG_LATCH	7u
#define ANODS_NO		12u
#define CATHODS_NO		8u

Drivers::LED led(13u);
Drivers::LedMatrixDriver matrix(ANODS_NO, CATHODS_NO, PIN_REG_CLK, PIN_REG_DATA, PIN_REG_LATCH);

void setup()
{
	printf_init(&Serial,  9600);

	printf("START\n");
	matrix.ClearAll();
}

void ledBlink()
{
	static uint32_t prevMillis = 0;
	static uint8_t state = 0;

	if( state == 0 )
	{
		if( millis() - prevMillis >= 1000 )
		{
			prevMillis = millis();
			led.On();
			state = 1;
		}
	}
	else if( state == 1 )
	{
		if( millis() - prevMillis >= 50 )
		{
			prevMillis = millis();
			led.Off();
			state = 0;
		}
	}
}

void updateDisplay()
{
	static uint32_t prevMillis = 0;
	static uint8_t flag = 0;

	uint8_t heart[8][12] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

	if( millis() - prevMillis >= 1000 )
	{
		prevMillis = millis();
		if( flag == 1)
		{
			flag = 0;
			matrix.LoadFrame(heart);
		}
		else
		{
			matrix.ClearAll();
			flag = 1;
		}
	}
}

void loop()
{
	updateDisplay();
	matrix.MainFunction();

	ledBlink();
}


