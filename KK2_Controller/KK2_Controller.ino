#include <Servo.h>

Servo AIL, ELE, THR, RUDD;
int AILpin = 2,
	ELEpin = 3,
	THRpin = 4,
	RUDDpin = 5;


void setup()
{
	Serial.begin(9600);
	
	AIL.attach(AILpin);
	ELE.attach(ELEpin);
	THR.attach(THRpin);
	RUDD.attach(RUDDpin);
}

void loop()
{
	THR.write(map(analogRead(A7), 0, 1023, 90, 165));
	//Serial.println(analogRead(A7));

	if (Serial.available() > 0) 
	{
		int d, a;
		a = 1;
		
		d = Serial.read();
		switch (d)
		{
		case'a':
			Serial.println("arming.....");
			THR.write(0);
			RUDD.write(180);
			delay(1000);
			RUDD.write(90);
			Serial.println("ARMED......");
			break;

		case 'b':
			THR.write(90);
			Serial.println("MIN");
			break;

		case 'c':
			THR.write(135);
			Serial.println("MED");
			break;

		case 'e':
			THR.write(180);
			Serial.println("MAX");
			break;

		case 'd':
			Serial.println("Disarming.....");
			THR.write(0);
			delay(1000);
			THR.write(0);
			RUDD.write(0);
			delay(1000);
			RUDD.write(90);
			Serial.println("DISARMED......");
			break;
		}
	}
}
