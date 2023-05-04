#include <HC595.h>
#include <LED.h>

#define REG_CLK		3u
#define REG_LATCH	7u
#define	REG_DATA	5u

Drivers::LED led(13);
Drivers::HC595 reg(REG_CLK, REG_DATA, REG_LATCH, 3);

void setup()
{
	led.Off();
	reg.ClearAll();
}

uint64_t prevMillis = 0;
void loop()
{
	if( millis() - prevMillis >= 500 )
	{
		prevMillis = millis();
		reg.ToggleAll();
		led.Toggle();
	}

	reg.MainFunction();
}
