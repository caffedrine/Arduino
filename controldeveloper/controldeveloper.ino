#include <Arduino.h>
#include <esp32-hal-dac.h>

#include "connection.h"
#include "DRV8835_ESP32_MotorsDriver.h"
#include "my_util.h"

//Motor pins
int motorLeft_IN1  = 25;	//Phase
int motorLeft_IN2  = 14; 	//Enable
int motorRight_IN1 = 26;	//Phase
int motorRight_IN2 = 27;	//Enable

//Encoders (IR Sensor: QRE1113)
int encoderLeftPin = 35;
int encoderRightPin = 39;

//Functions prototypes
void parseData();
void updateEncoders();

//Namespace with util functions prototype
namespace utils
{
	void writePeriodicData(String data, int interval = 1000);
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
    //Encoders PINS are set as INPUTS
	pinMode(encoderLeftPin, INPUT);
	pinMode(encoderRightPin, INPUT);

    Serial.begin(115200);
    Serial.println("---STARTING---");


    conn::setupAP();
    server.begin();
    conn::waitForServerClients();
    //*/
}

int speed = 0;
void loop()
{

	/*
	//Wifi link - check if client is still connected
	if(!client || !client.connected())
		conn::waitForServerClients();

	//Check if client have a command for us
	if(client.available())
	{
		String recvMsg = conn::readString();
		Serial.print(recvMsg);

		conn::writeString("Command(s) received...");
	}
	//*/

	if (Serial.available() > 0)
	{
		speed = Serial.parseInt();
	}


	//Get exact number of steps since last time
	//printPeriodicData(to_string(leftSteps) + "\t" + to_string(rightSteps), 50);
	//*/
}

void parseData(String *data)
{
	//Format of data we receive: [0;-100;0] or [0;-100;0]#[0;-100;0]#[0;-100;0]
	return;
}
