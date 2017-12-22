#include <string.h>
#include <SoftwareSerial\SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

int pinMotor = 11;
int testLed = 13;


void setup()
{
	Serial.begin(9600);
	bluetooth.begin(9600);

	pinMode(testLed, OUTPUT);
	pinMode(pinMotor, OUTPUT);
}

String serialString = "";
int DC = 1;

void loop()
{
	//Debugging
	//if (bluetooth.available()) Serial.write(bluetooth.read());
	//if (Serial.available()) bluetooth.write(Serial.read());

	setSpeed();	
	while (bluetooth.available())
	{
		char c = bluetooth.read();
		serialString += c;
		delay(2);
	}

	if (serialString.length() > 0)
	{
		updateParams(serialString);
		//displayParams();
		serialString = "";
	}
	//*/
}

void setSpeed()
{
	digitalWrite(pinMotor, HIGH);
	delayMicroseconds(DC); // Approximately 100% duty cycle @ 1KHz
	digitalWrite(pinMotor, LOW);
	delayMicroseconds(1000 - DC);
}

void updateParams(String recvString)
{
	String buffer = "";
	String paramName = "";
	String paramValue = "";

	for (int i = 0; i < recvString.length(); i++)
	{
		if (recvString[i] != ';')
		{
			buffer += recvString[i];
		}
		else if (recvString[i] == ';')
		{
			paramName = buffer.substring(0, buffer.indexOf('='));
			paramValue = buffer.substring(paramName.length() + 1);

			buffer = "";

			if (paramName == "d") DC = to_int(paramValue);
		}
	}
}

void displayParams()
{
	//Debugging
	String DCS = "";
	DCS += "Factor de umplere: ";
	DCS += to_string(DC);
	Serial.println(DCS);

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
