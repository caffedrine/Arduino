#include <string.h>

HardwareSerial & dbgSerial = Serial;
HardwareSerial & esp8266 = Serial2;

void setup()
{
	//Just for debugger to automatically adjust to 9600
	Serial.begin(38400);
	
	dbgSerial.begin(38400);
	esp8266.begin(38400);
	delay(2000);
	setupWifi();
}

void loop()
{	
	if (dbgSerial.available()) esp8266.write(dbgSerial.read());
	if (esp8266.available()) dbgSerial.write(esp8266.read());
	
	keepWifiLink();
}

bool setupWifi()
{
	esp8266.println("AT+CIPMUX=1");
	delay(500);
	esp8266.println("AT+CIPSERVER=1,1337");
	delay(500);
}

void keepWifiLink()
{
	static int interval = 5000;
	static long prevTime = 0;
	static int action = 0;
	// Action 0: AT+CIPMUX=1
	// Action 1: AT+CIPSERVER=1,1337

	if (millis() - prevTime > interval)
	{
		prevTime = millis();
		if (action == 0)
		{
			esp8266.println("AT+CIPMUX=1");
			action = 1;
		}
		else
		{
			esp8266.println("AT+CIPSERVER=1,1337");
			action = 0;
		}
	}
}