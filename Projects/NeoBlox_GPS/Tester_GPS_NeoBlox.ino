#include <string.h>

#include <NeoSWSerial\NeoSWSerial.h>
#include <TinyGPS++.h>

#include <Servo\src\Servo.h>

NeoSWSerial gpsSerial(51, 50);
TinyGPSPlus gps;

String serialString = "";

void handleRxChar(uint8_t c)
{

	if (c != '\n')
	{
		serialString += (char)c;
		//gps.encode((char)c);
		//Serial.write(c);
	}
	else
	{
		for (int i = 0; i < serialString.length(); i++)
		{
			gps.encode(serialString[i]);
		}

		if (gps.altitude.isUpdated())
		{
			Serial.print("Alt: "); Serial.print(gps.altitude.meters()); Serial.print("\n");
		}

		if (gps.location.isUpdated())
		{
			Serial.print("Lat: "); Serial.print(gps.location.lat(), 6); Serial.print("\n");
			Serial.print("Long: "); Serial.print(gps.location.lng(), 6); Serial.print("\n");
			Serial.print("\n");
		}
		serialString = "";
	}
}

void setup()
{
	gpsSerial.attachInterrupt(handleRxChar);
	gpsSerial.begin(9600);
	Serial.begin(9600);
}

void loop()
{

}
//*/
/*
#include <AltSoftSerial.h>
#include <TinyGPS++.h>

AltSoftSerial gpsSerial; //TX:9, RX:8 (UNO) - Mega: 46-48
TinyGPSPlus gps;

void setup() 
{
	Serial.begin(9600);
	gpsSerial.begin(9600);
}

void loop()
{
	while (gpsSerial.available())
	{
		Serial.write(gpsSerial.read());
		//gps.encode(gpsSerial.read());
	}

	if (gps.altitude.isUpdated())
	{
		Serial.print("Alt: "); Serial.print(gps.altitude.meters()); Serial.print("\n");
	}

	if (gps.location.isUpdated())
	{
		Serial.print("Lat: "); Serial.print(gps.location.lat(), 6); Serial.print("\n");
		Serial.print("Long: "); Serial.print(gps.location.lng(), 6); Serial.print("\n");
		Serial.print("\n");
	}
}
//*/
