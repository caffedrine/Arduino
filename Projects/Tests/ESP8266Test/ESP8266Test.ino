#include <SevSeg\SevSeg.h>
#include <SoftwareSerial\SoftwareSerial.h>

#define debug true

//Use these when on AP mode
#define AP_SSID "Drona"
#define AP_PASS "no_password"

//Use these as router credentials
#define SSID "Drona"
#define PASS "no_password"

//SoftwareSerial Serial2(51, 50);

int potPin = A15;
int connLed = 31; //this led is on when wifi connection were established!

void setup()
{
	pinMode(connLed, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(potPin, INPUT);

	Serial.begin(9600);
	Serial2.begin(9600);

	//setupWifiConn("P2P");
	//digitalWrite(connLed, HIGH);
	//start();
}

void loop()
{	
	if (Serial.available()) Serial2.write(Serial.read());
	if (Serial2.available())
	{
		//if (debug) msg(esp8266.readStringUntil('\0'));
		if ( Serial2.find("+IPD,") )
		{
			delay(200); // wait for the serial buffer to fill up (read all the serial data)
			// get the connection id so that we can then disconnect
			int connectionId = Serial2.read() - 48; // subtract 48 because the read() function returns 
			// the ASCII decimal value and 0 (the first decimal number) starts at 48

			if (Serial2.find("pin=")) // advance cursor to "pin="
			{
			//int pinNumber = (esp8266.read() - 48) * 10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
			//pinNumber += (esp8266.read() - 48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
			//only if pin have two numbers
			int pinNumber = Serial2.read() - 48;
			if (debug) msg("We have pin to toggle: " + to_string(pinNumber));

			digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin

			}
		}
	}
}

void start()
{
	Serial.println(sendCommand("AT+RST")); // Perform a reset before all
	Serial.println(sendCommand("AT+CWMODE=1")); // First mode, only can join to APs
	
	// Can't be concated directly because of defines
	String comm = "AT+CWJAP=\"";
	comm += SSID;
	comm += "\",\"";
	comm += "\"";
	Serial.println(sendCommand(comm)); // Connecting to router with given credentials
	
	Serial.println(sendCommand("AT+CIFSR")); // Show alocated IP addres by router
	Serial.println(sendCommand("AT+CIPMUX=0"));// Only one connection needed
}

String sendCommand(String command)
{
	unsigned long timeout = 20000; //set timeout 20 seconds
	unsigned long t = millis(); // time when function starts

	Serial2.println(command); // Sending command to esp then starts counting time
	if (debug)
	{
		String response = "========Start Command========\n";
		response += "Command: " + command + "\n";
		response += "Esp response: ";

		while (!Serial2.available())
		{
			//The esp has not returned anything yet, so we have to wait;
			delay(50);
			if (millis() - t > timeout)
			{
				response += "TIMEOUT";
				response += "\n========End Command==========\n";
				return response;
			}
		}

		while (Serial2.available())
		{
			response += Serial2.readStringUntil('\0');
		}
		response += "\n========End Command==========\n";

		return response;
	}
	else
	{
		while (!Serial2.available())
		{
			//The esp has not returned anything yet, so we have to wait;
			delay(50);
			if (millis() - t > timeout)
				return "TIMEOUT";
		}

		String response;
		while (Serial2.available())
		{
			response += Serial2.readStringUntil('\0');
		}
		return response;		
	}


	/*
	unsigned long del = 200;

	if (strstr(command.c_str(), "AT+RST"))
		del = 100;
	else if (strstr(command.c_str(), "AT+CWJAP"))
		del = 10000;
	else if (strstr(command.c_str(), "AT+CWSAP"))
		del = 10000;

	String response = "========Start Command========\n";
	Serial2.println(command);
	delay(del);

	while (Serial2.available())
	{
		response += Serial2.readStringUntil('\0');
	}
	response += "\n========End Command==========\n";

	return response;
	*/
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

	if (mode == "AP") connComm += AP_SSID;
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

	delay(8000);

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

	/*
	if (((strstr(RST.c_str(), "OK") != NULL) || (strstr(RST.c_str(), "ready") != NULL)) &&
		((strstr(CWMODE.c_str(), "OK") != NULL) || (strstr(CWMODE.c_str(), "no change") != NULL)) &&
		(strstr(CONNCOM.c_str(), "OK") != NULL) &&
		(strstr(CIFSR.c_str(), "OK") != NULL) &&
		(strstr(CIPMUX.c_str(), "OK") != NULL) &&
		(strstr(CIPSERVER.c_str(), "OK") != NULL))

		return true;
	else */
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

