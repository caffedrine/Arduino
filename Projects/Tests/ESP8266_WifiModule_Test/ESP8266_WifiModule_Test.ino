#include <string.h>
#include <stdlib.h>

#include <SoftwareSerial\SoftwareSerial.h>
#include <SevSeg\SevSeg.h>

#define debug true
#define SSID "2G"
#define PASS "jancazan"

#define AP_SSID "Drona"
#define AP_PASS "no_password"

SoftwareSerial esp8266(51, 50); //esp on 17, 16
SevSeg sevseg;

void setup()
{
	sevseg.setBrightness(90);

	Serial.begin(9600);
	esp8266.begin(9600);
	pinMode(8, OUTPUT);

	setupWifiConn("AP");
}

void loop()	
{	
	if( esp8266.available() )
	{
		//if (debug) msg(esp8266.readStringUntil('\0'));
		if (esp8266.find("+IPD,"))
		{
			delay(200); // wait for the serial buffer to fill up (read all the serial data)
			// get the connection id so that we can then disconnect
			int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns 
			// the ASCII decimal value and 0 (the first decimal number) starts at 48
			/*
			if (esp8266.find("pin=")) // advance cursor to "pin="
			{
				//int pinNumber = (esp8266.read() - 48) * 10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
				//pinNumber += (esp8266.read() - 48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
				//only if pin have two numbers
				int pinNumber = esp8266.read() - 48;
				if (debug) msg("We have pin to toggle: " + to_string(pinNumber));

				digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin  

			}
			*/

			if (esp8266.find("pv="))
			{
				int val = (esp8266.read() - 48) * 1000;
				if (val >= 0 && val <= 9)
					val = 0;
				
				int val2 = (esp8266.read() - 48) * 100;
				if (val2 < 900 && val2 >= 0)
					val += val2;
				
				int val3 = (esp8266.read() - 48) * 10;
				if (val3 < 90 && val3 >= 0)
					val += val3;

				int val4 = (esp8266.read() - 48);
				if (val4 < 9 && val4 >= 0)
					val += val4;

				if (val % 10 == 0 && val4 != 0)
				{
					val = val / 10;
					if (val % 10 == 0 && val3 != 0)
					{
						val = val / 10;
						if (val % 10 == 0 && val2 != 0)
							val = val / 10;
					}
				}

				if (debug) msg("We have a potentiometter value set: " + to_string(val));
			}
		}

	}
}

String sendCommand(String command)
{
	unsigned long del = 500;

	if (strstr(command.c_str(), "AT+RST"))
		del = 100;
	else if (strstr(command.c_str(), "AT+CWJAP"))
		del = 10000;
	else if (strstr(command.c_str(), "AT+CWSAP"))
		del = 10000;

	String response = "========Start Command========\n";
	esp8266.println(command);
	delay(del);

	while (esp8266.available())
	{
		response += esp8266.readStringUntil('\0');
	}
	response += "\n========End Command==========\n";

	return response;
}

bool setupWifiConn(String mode)
{
	String RST = sendCommand("AT+RST");
	if (strstr(RST.c_str(), "OK") != NULL || strstr(RST.c_str(), "ready") != NULL)
	{
		if (debug)
			Serial.println(RST);
	}
	else
		delay(3000);

	String CWMODE = "";
	if (mode == "AP")
		CWMODE = sendCommand("AT+CWMODE=2");
	else
		CWMODE = sendCommand("AT+CWMODE=3");

	if (strstr(CWMODE.c_str(), "OK") != NULL || strstr(CWMODE.c_str(), "no change") != NULL)
	{
		if (debug)
			Serial.println(CWMODE);
	}
	else
		delay(3000);

	String connComm = "";
	if (mode == "AP") connComm = "AT+CWSAP=\"";
	else connComm = "AT+CWJAP=\"";

	if(mode == "AP") connComm += AP_SSID;
	else connComm += AP_PASS;
	
	connComm += "\",\"";
	
	if (mode == "AP") connComm += AP_PASS;
	else connComm += PASS;
	
	if (mode == "AP")
		connComm += "\",3,0";
	else
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
	//Only for debuging
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

void msg(String msg)
{
	Serial.println("\n************Debug msg************");
	Serial.println(msg);
	Serial.println("************END Debug************");
}

String to_string(int val)
{
	char snum[16];
	itoa(val, snum, 10);
	return snum;
}

