#include "Arduino.h"
#include <LedMatrixDriver.h>
#include <LED.h>

#define HC595_DEBUG_MESSAGES	1
#define HC595_DEBUG_ENABLED		1


#define PIN_REG_DATA	5u
#define PIN_REG_CLK		3u
#define PIN_REG_LATCH	7u
#define ANODS_NO		12u
#define CATHODS_NO		8u

Drivers::LED led(13u);
//Drivers::LedMatrixDriver matrix(CATHODS_NO, ANODS_NO, PIN_REG_CLK, PIN_REG_DATA, PIN_REG_LATCH);

Drivers::HC595 reg(PIN_REG_CLK, PIN_REG_DATA, PIN_REG_LATCH, 2);

void setup()
{
	Serial.begin(9600);
	Serial.println("START");
	//matrix.ClearAll();
	reg.ClearAll();
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
	static uint8_t state = 0;

//	if( millis() - prevMillis >= 1000 )
//	{
//		prevMillis = millis();
//
//		reg.ToggleAll();
//
//		//matrix.IncrementMatrix();
//	}

	if( state == 0 )
	{
		if( millis() - prevMillis >= 500 )
		{
			prevMillis = millis();
			reg.SetLastNBits(7);
			state = 1;
		}
	}
	else if( state == 1 )
	{
		if( millis() - prevMillis >= 200 )
		{
			prevMillis = millis();
			reg.ClearLastNBits(7);
			state = 0;
		}
	}

}

void loop()
{
	updateDisplay();
	//matrix.MainFunction();

	ledBlink();
	reg.MainFunction();
}


