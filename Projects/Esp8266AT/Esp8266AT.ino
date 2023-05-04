#include "Arduino.h"
#include <WiFiEspAT.h>


WiFiServer server(443);

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Serial.println("Application starting");

	Serial1.begin(115200);
	WiFi.init(Serial1);

	while(1)
	{
		while( Serial.available() )
		{
			Serial1.print(Serial.readString());
		}

		while( Serial1.available() )
		{
			Serial.print(Serial1.readString());
		}
	}


	if (WiFi.status() == WL_NO_MODULE)
	{
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		while (true)
			;
	}

	// waiting for connection to Wifi network set with the SetupWiFiConnection sketch
	Serial.println("Waiting for connection to WiFi");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.print('.');
	}
	Serial.println();

	server.beginSSL();

	IPAddress ip = WiFi.localIP();
	Serial.println();
	Serial.println("Connected to WiFi network.");
	Serial.print("To access the server, enter \"https://");
	Serial.print(ip);
	Serial.println("/\" in web browser.");
}

// The loop function is called in an endless loop
void loop()
{
	WiFiClient client = server.available();
	if (client)
	{ // true only for a connected client with data available
		IPAddress ip = client.remoteIP();
		Serial.print("new client ");
		Serial.println(ip);

		while (client.connected())
		{
			if (client.available())
			{
				char line[128];
				size_t l = client.readBytesUntil('\n', (uint8_t*) line, sizeof(line));
				if (l == 0)
				{
					Serial.print("error reading request");
					break;
				}
				line[l - 1] = 0; // overwrite \r with a 0
				Serial.println(line);

				if (strlen(line) == 0)
				{ // http headers end with an empty line
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");  // the connection will be closed after completion of the response
					client.println("Refresh: 5");  // refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");

					// output the value of analog input pins
					for (int analogChannel = 0; analogChannel < 4; analogChannel++)
					{
						int sensorReading = analogRead(analogChannel);
						client.print("analog input ");
						client.print(analogChannel);
						client.print(" is ");
						client.print(sensorReading);
						client.println("<br />");
					}
					client.println("</html>");
					break;
				}
			}
		}

		// close the connection:
		client.stop();
		Serial.println("client disconnected");
	}
}
