#include <string.h>
#include <SoftwareSerial\SoftwareSerial.h>

#define DEBUG true
#define SSID "2G"
#define PASS "internatcamin!!!"

SoftwareSerial esp8266(53, 52); //esp on 17, 16

void setup()
{
	Serial.begin(9600);
	esp8266.begin(9600);

	pinMode(10, OUTPUT);

	connect(DEBUG);
}

void loop()
{
	//wifiConnected();
	//delay(5000);
	
	if (esp8266.available())
	{
		if (esp8266.find("+IPD,"))
		{
			delay(200); // wait for the serial buffer to fill up (read all the serial data)
			// get the connection id so that we can then disconnect
			int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns 
			// the ASCII decimal value and 0 (the first decimal number) starts at 48

			esp8266.find("pin="); // advance cursor to "pin="

			int pinNumber = (esp8266.read() - 48) * 10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
			pinNumber += (esp8266.read() - 48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number

			digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin    

			// make close command
			//String closeCommand = "AT+CIPCLOSE=";
			//closeCommand += connectionId; // append connection id
			//closeCommand += "\r\n";

			//sendData(closeCommand, 1000, DEBUG); // close connection
		}
	}
}

bool connect(bool debug)
{
	String RST = sendCommand("AT+RST");
	if (strstr(RST.c_str(), "OK") != NULL || strstr(RST.c_str(), "ready") != NULL)
	{
		if (debug)
			Serial.println(RST);
	}
	else
		delay(3000);

	String CWMODE = sendCommand("AT+CWMODE=3");
	if (strstr(CWMODE.c_str(), "OK") != NULL || strstr(CWMODE.c_str(), "no change") != NULL)
	{
		if (debug)
			Serial.println(CWMODE);
	}
	else
		delay(3000);

	String connComm = "AT+CWJAP=\"";
	connComm += SSID;
	connComm += "\",\"";
	connComm += PASS;
	connComm += "\"";
	String CONNCOM = sendCommand(connComm);
	if (strstr(CONNCOM.c_str(), "OK") != NULL)
	{
		if (debug)
			Serial.println(CONNCOM);
	}
	else
		delay(10000);

	//this will print ip address where connected to
	String CIFSR = sendCommand("AT+CIFSR");
	if (strstr(CIFSR.c_str(), "OK") != NULL)
	{
		if (debug)
			Serial.println(CIFSR);
	}
	else
		delay(3000);

	//Acting as TCP server to accept connections from now
	String CIPMUX = sendCommand("AT+CIPMUX=1"); //accept mltiple connections
	if (strstr(CIPMUX.c_str(), "OK") != NULL)
	{
		if (debug)
			Serial.println(CIPMUX);
	}
	else
		delay(3000);

	// acting as a server on port 1337, works with telnet
	String CIPSERVER = sendCommand("AT+CIPSERVER=1,1337");
	if (strstr(CIPSERVER.c_str(), "OK") != NULL)
	{
		if (debug)
			Serial.println(CIPSERVER);
	}
	else
		delay(3000);
	/*
	Serial.println("********");
	Serial.println(RST);
	Serial.println(CWMODE);
	Serial.println(CONNCOM);
	Serial.println(CIFSR);
	Serial.println(CIPMUX);
	Serial.println(CIPSERVER);
	Serial.println("********");
	*/

	if (((strstr(RST.c_str(), "OK") != NULL) || (strstr(RST.c_str(), "ready") != NULL)) &&
		((strstr(CWMODE.c_str(), "OK") != NULL) || (strstr(CWMODE.c_str(), "no change") != NULL)) &&
		(strstr(CONNCOM.c_str(), "OK") != NULL) &&
		(strstr(CIFSR.c_str(), "OK") != NULL) &&
		(strstr(CIPMUX.c_str(), "OK") != NULL) &&
		(strstr(CIPSERVER.c_str(), "OK") != NULL))

		return true;
	else
		return false;
}

String sendCommand(String command)
{
	unsigned long del = 200;

	if (strstr(command.c_str(), "AT+RST"))
		del = 500;
	else if (strstr(command.c_str(), "AT+CWJAP"))
		del = 10000;

	String response = "========Start Command========\n";
	esp8266.println(command);
	delay(del);

	while (esp8266.available())
	{
		response += esp8266.readStringUntil('\0');
	}
	response += "\n========End Command========\n";

	return response;
}

