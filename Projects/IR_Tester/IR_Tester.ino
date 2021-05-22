#include <IRremote\IRremote.h>
#include <IRremote\IRremoteInt.h>

int led = 5;
int IRpin = A2;

IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
	pinMode(led, OUTPUT);
	irrecv.enableIRIn(); // Start the receiver
}

void loop()
{	
	if (irrecv.decode(&results))
	{
		Serial.println(results.value, DEC); // Print the Serial 'results.value'
		irrecv.resume();   // Receive the next value

		if (results.value == 3810010651)
		{
			digitalWrite(led, !digitalRead(led));
		}
	}

	/*
	digitalWrite(led, HIGH);
	delay(1000);
	*/
}
