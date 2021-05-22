#include <SoftwareSerial.h>

int LED = 9;     // Led conectat la pinul 9 ( ledul activ in cazul impactului)
int LED1 = 10;   // Led conectat la pinul 10 (ledul activ cand senzorul nu este actionat)

int sensor = 7;  // Pinul de intrare in Arduino ( pinul 'out' de la senzor)
bool out = HIGH;  // HIGH - nu detecteaza obstacol

#define numar 0757

SoftwareSerial GSM(2, 3); // GSM TX-RX


void setup() 
{
	pinMode(LED, OUTPUT);
	pinMode(LED1, OUTPUT);
	pinMode(sensor, INPUT);
	
	Serial.begin(9600);
	GSM.begin(9600);

	delay(1000); //Pentru initializare modul GSM
}

void loop() 
{
	out = digitalRead(sensor);

	if (out == LOW)
	{
		Serial.println(" ------ C  R  A  S  H ------");
		digitalWrite(LED, HIGH);
		digitalWrite(LED1, LOW);

		sendAlert();
	}
	else
	{
		digitalWrite(LED, LOW);
		digitalWrite(LED1, HIGH);
		Serial.println(" _ ");
	}
	delay(200);
}

void sendAlert(void)
{
	Serial.println("Sending SMS...");

	//Set SMS format to ASCII
	GSM.write("AT+CMGF=1\r\n");
	delay(1000);

	//Send new SMS command and message number
	GSM.write("AT+CMGS=\"07577\"\r\n");
	delay(1000);

	//Send SMS content
	GSM.write("A avut loc un accident si este nevoie urgenta de ajutor"); //eventual pune si un GPS si trimite coordonatele prin mesaj :P
	delay(1000);

	//Send Ctrl+Z / ESC to denote SMS message is complete
	GSM.write((char)26);
	delay(1000);

	Serial.println("SMS Sent!");
}


