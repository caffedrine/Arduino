#include <Servo.h>

int potPin = A15;
Servo m1, m2, m3, m4;

int pm1 = 2,
	pm2 = 3,
	pm3 = 4,
	pm4 = 5;

void setup()
{
	pinMode(potPin, INPUT);
	pinMode(pm1, OUTPUT);
	pinMode(pm2, OUTPUT);
	pinMode(pm3, OUTPUT);
	pinMode(pm4, OUTPUT);

	Serial.begin(9600);
	
	m1.attach(pm1); delay(1); m1.write(40);
	m2.attach(pm2); delay(1); m2.write(40);
	m3.attach(pm3); delay(1); m3.write(40);
	m4.attach(pm4); delay(1); m4.write(40);
}

int throttle = 0;
void loop()
{
	throttle = analogRead(potPin);
	Serial.println(throttle);

	throttle = map(throttle, 0, 1023, 0, 179);
	
	m1.write(179-throttle);
	m2.write(throttle);
	m3.write(179-throttle);
	m4.write(throttle);
}
