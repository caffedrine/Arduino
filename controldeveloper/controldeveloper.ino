#include <Arduino.h>

#include <WiFi.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <esp32-hal-dac.h>

#include "my_util.h"

//AP Credentials. Those will be used in our Java applicaion.
const char *AP_Name   = "LAB_ROVER_1";
const char *AP_Passwd = "LabRover@Passwd";

//Led which will indicate data transfers
int connectionLedIndicator = 5;
int trafficLedIndicator = 5;

//Motor pins
int motorLeft_IN1  = 25;	//Phase
int motorLeft_IN2  = 14; 	//Enable

int motorRight_IN1 = 26;	//Phase
int motorRight_IN2 = 27;	//Enable

//Setting up server on specified port
WiFiServer server(1337, 1);
WiFiClient client;

//Functions prototypes
void parseData();

//Connection manage namespace prototype
namespace conn
{
	void setupAP();
	void waitForWifiClients();
	void waitForServerClients();
	bool writeString(String data);
	String readString();
	bool isWritable();
	void connectionLedIndicator();
}

//Namespace with util functions prototype
namespace utils
{
	void writePeriodicData(String data, int interval);
	void printPeriodicData(String data, int interval);
}

//Commands structure
typedef struct Command
{
	int commandID;
	int degrees;
	float time;
	int anotherVar;
}command;

void setup()
{
	//Leds
    pinMode(trafficLedIndicator, OUTPUT);
    pinMode(connectionLedIndicator, OUTPUT);

    //Motors
    pinMode(motorLeft_IN1, OUTPUT);
    pinMode(motorRight_IN1, OUTPUT);
    pinMode(motorLeft_IN2, OUTPUT);
    pinMode(motorRight_IN2, OUTPUT);

    //Make sure motors are stopped
	digitalWrite(motorLeft_IN2, LOW);
	digitalWrite(motorRight_IN2, LOW);

    Serial.begin(115200);
    Serial.println("---STARTING---");

    /*
    conn::setupAP();
    server.begin();
    conn::waitForServerClients();
    //*/
}

int p = 0;
long speed = 0;

void loop()
{
	/*
	if(!client || !client.connected())
		conn::waitForServerClients();

	if(client.available())
	{
		String recvMsg = conn::readString();
		Serial.print(recvMsg);

		conn::writeString("Command(s) received...");
	}
	utils::writePeriodicData("Command(s) executed...", 5000);
	//*/

	if (Serial.available() > 0)
	{
		speed = Serial.parseInt();
	}

	digitalWrite(motorLeft_IN2, HIGH);
	digitalWrite(motorRight_IN2, HIGH);



	//dacWrite(motorLeft_IN1, speed);
	//dacWrite(motorRight_IN1, speed);

	utils::printPeriodicData("Curr speed: " + to_string(speed), 1000);
	//*/
}

void parseData(String *data)
{
	//Format of data we receive: [0;-100;0] or [0;-100;0]#[0;-100;0]#[0;-100;0]
	return;
}

namespace conn
{
	//function used to initialize WiFi module in AP Mode
	void setupAP()
	{
		//Configure chip on AP mode
		Serial.print("Configuring AP...");
		WiFi.mode(WIFI_AP);
		bool AP_Created = WiFi.softAP(AP_Name, AP_Passwd);
		AP_Created ? Serial.println( "done" ) : Serial.println( "failed" );

		//Print AP IP Address
		IPAddress apIP = WiFi.softAPIP();
		Serial.print("AP IP Address: "); Serial.println(apIP);
	}

	//Loop to wait for wifi clients in case of connection lost
	void waitForWifiClients()
	{
		Serial.print("Waiting for Wi-Fi clients...");
		while(WiFi.softAPgetStationNum() == 0)
		{
			delay(600);
			connectionLedIndicator();
		}
		Serial.println("done");

		pinMode(trafficLedIndicator, OUTPUT);
		digitalWrite(trafficLedIndicator, LOW);
	}

	//Loop to wait for clients to open tcp sockets
	void waitForServerClients()
	{
		//Maybe socket stopped because link was lost because of WiFi disconnect
		delay(100); //We need this delay to get update values of WiFi Clients
		if(WiFi.softAPgetStationNum() == 0)
			conn::waitForWifiClients();

		Serial.print("Waiting for socket clients...");
		while(!client || !client.connected())
		{
			connectionLedIndicator();
			delay(250);
			client = server.available();

			//In the meanwhile AP may be disconnected - we may want to check
			if(WiFi.softAPgetStationNum() == 0)
			{
				Serial.println("failed");
				conn::waitForWifiClients();
				Serial.print("Waiting for socket clients...");
			}
		}
		client.setNoDelay(true);
		Serial.println( "done" );

		pinMode(trafficLedIndicator, OUTPUT);
		digitalWrite(trafficLedIndicator, LOW );
	}

	//Function to write to client TCP socket
	bool writeString(String content)
	{
		digitalWrite(trafficLedIndicator, HIGH);

		if(!isWritable())
		{
			digitalWrite(trafficLedIndicator, LOW);
			return false;
		}

		int result = client.println(content); delay(2);
		if(result < 1)
		{
			digitalWrite(trafficLedIndicator, LOW);
			return false;
		}

		digitalWrite(trafficLedIndicator, LOW);//*/
		return true;
	}

	//Read string from client TCP socket
	String readString()
	{
		digitalWrite(trafficLedIndicator, HIGH);
		String result = client.readString();
		digitalWrite(trafficLedIndicator, LOW);//*/
		return result;
	}

	//check if client socket is writable
	bool isWritable()
	{
		int result = client.print(">");
		delay(4); //wait for register with error to be filled up
		if(!result)
			return false;

		result = client.print('>');
		delay(4); //wait for register with error to be filled up
		if(!result)
			return false;

		return true;
	}

	//Indicate via leds connection status
	void connectionLedIndicator()
	{
		static long previousMillis = 0;
		if (millis() - previousMillis > 400)
		{
			previousMillis = millis();

			pinMode(trafficLedIndicator, INPUT);
			bool currStatus = digitalRead(5);

			pinMode(trafficLedIndicator, OUTPUT);
			digitalWrite(trafficLedIndicator, currStatus?0:1 );
		}
	}
}

namespace utils
{
	void writePeriodicData(String data, int interval = 1000)
	{
		static long previousMillis = millis();
		if (millis() - previousMillis > interval)
		{
			previousMillis = millis();
			conn::writeString(data);
		}
	}

	void printPeriodicData(String data, int interval = 1000)
	{
		static long previousMillis = 0;
		if (millis() - previousMillis > interval)
		{
			previousMillis = millis();
			Serial.println(data);
		}
	}
}
