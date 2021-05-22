
// include the library code:
#include <LiquidCrystal\LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("hello, world!");
}

void loop() {
	// Turn off the display:
	lcd.noDisplay();
	delay(500);
	// Turn on the display:
	lcd.display();
	delay(500);
}


/*
#include <LiquidCrystal595\LiquidCrystal595.h>

int latchPin = 5; // RCK - ST_CP
int clockPin = 6; // SCK - SH_CP
int dataPin = 4;  // DS (SER)

LiquidCrystal595 lcd(dataPin, latchPin, clockPin);
void setup() 
{
	lcd.begin(16, 2); // 16 characters, 2 rows

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Wow. 3 pins!");
	lcd.setCursor(0, 1);
	lcd.print("Fabulous");
}

void loop() 
{
	lcd.begin(16, 2); // 16 characters, 2 rows

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Wow. 3 pins!");
	lcd.setCursor(0, 1);
	lcd.print("Fabulous");
}
*/