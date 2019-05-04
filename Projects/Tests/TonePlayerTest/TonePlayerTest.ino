#include "TonePlayer.h"

TonePlayer tone1(TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L); // pin D9 (Uno), D11 (Mega)

void setup()
{
	pinMode(9, OUTPUT);  // output pin is fixed (OC1A)
	//tone1.tone(10);  // 220 Hz
}

void loop()
{


}
