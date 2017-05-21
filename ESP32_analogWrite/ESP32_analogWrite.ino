#include "Arduino.h"
#include <esp32-hal-ledc.h>

#include "my_util.h"

int analogOutputPin = 5;
int analogInputPin = 36;

//prototypes
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 4095);

void setup()
{
	Serial.begin(115200);
	pinMode(analogOutputPin, OUTPUT);
	pinMode(analogInputPin, INPUT);

	//Setting up
	ledcSetup(1, 5000, 13); //Channel 1; 5000Hz; 13 bits resolution
	ledcAttachPin(analogOutputPin, 0);
}

int writtenVal = 0;
int readedVal = 0;

void loop()
{
	if(Serial.available())
			writtenVal = to_int(Serial.readString());
	readedVal = analogRead(analogInputPin);

	ledcAnalogWrite(0, writtenVal);

	//We want to make sure about value we write, so we read the value using another port
	readedVal = analogRead(analogInputPin);

	//Print data for debugging
	printPeriodicData("Current speed: " + to_string(writtenVal) + "\t Readed val: " + readedVal, 1000);
}

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax)
{
	// calculate duty, 8191 from 2 ^ 13 - 1
	uint32_t duty = (8191 / valueMax) * min(value, valueMax);

	// write duty to LEDC
	ledcWrite(channel, duty);
}
