#include "I2Cdev\I2Cdev.h"
#include "MPU6050\MPU6050.h"
#include "Wire\Wire.h"
#include "SoftwareSerial\SoftwareSerial.h"

MPU6050 accelgyro;
SoftwareSerial bluetooth(2, 3);

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() 
{
	Wire.begin();
	Serial.begin(9600);
	bluetooth.begin(9600);
	accelgyro.initialize();

	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
	pinMode(4, OUTPUT);

}

String buffer = "";


void loop() 
{
	updateGyro();
	
	//DEBUGGING
	//if (bluetooth.available()) Serial.write(bluetooth.read());
	//if (Serial.available()) bluetooth.write(Serial.read());

	buffer = "aaa;d=" + to_string(ax) + ";";
	bluetooth.write(buffer.c_str());
	
	Serial.println(buffer);
	
	delay(400);
}

void updateGyro()
{
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	ax = map(ax, -18000, 18000, 1, 999);
	if (ax < 100)
		ax = 1;

}

String to_string(int val)
{
	char snum[16];
	itoa(val, snum, 10);
	return snum;
}

int to_int(String str)
{
	return atoi(str.c_str());
}