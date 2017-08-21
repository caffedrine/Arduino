/* SevSeg Counter Example
The unit we supply is common cathode, 12 pin. In this example and using this library, 12 pins are required on the Arduino – you could use shift registers to reduce this requirement but would need to use a different library.

The pin out when looking from above the display (or when placed on a breadboard) is as follows:

Top Row: 1,a,f,2,3,b
Bottom Row: e,d,dp,c,g,4
1,2,3,4 refer to digit cathode pins. a,b,c,d,e,f,g,dp refer to the individual segments – dp being the decimal point.

Use 1kΩ resistors in series on the cathode pins, and wire theses to D2-D5 on the Arduino. Wire the segment pins (a-g,dp) to D6-D13.

So the top row should be wired as follows, from left to right:

1kΩ resistor then to D2
D6
D11
1kΩ resistor then to D3
1kΩ resistor then to D4
D7
And the bottom row, again from left to right:

D10
D9
D13
D8
D12
1kΩ resistor then to D5
*/

#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object

int pinPot = A15; //potentiometter

void setup() 
{
	pinMode(42, OUTPUT);
	pinMode(43, OUTPUT);
	pinMode(44, OUTPUT);
	pinMode(45, OUTPUT);
	pinMode(46, OUTPUT);
	pinMode(47, OUTPUT);
	pinMode(48, OUTPUT);
	pinMode(49, OUTPUT);
	pinMode(50, OUTPUT);
	pinMode(51, OUTPUT);
	pinMode(52, OUTPUT);
	pinMode(53, OUTPUT);
	
	byte numDigits = 4;
	byte digitPins[] = { 42, 43, 44, 55 };
	byte segmentPins[] = { 46, 47, 48, 49, 50, 51, 52, 53 };

	//or COMMON_ANODE
	sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
	sevseg.setBrightness(90);

	pinMode(pinPot, INPUT);
	Serial.begin(9600);
}

void loop() 
{
	int potVal = analogRead(pinPot);
	Serial.println(potVal);
	
	sevseg.setNumber(potVal, 0);
	sevseg.refreshDisplay(); // Must run repeatedly
}

