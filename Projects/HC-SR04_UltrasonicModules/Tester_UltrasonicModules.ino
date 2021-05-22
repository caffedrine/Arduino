/*
Programul furnizeaza rezultatul primit de la senzorii ultrasonici din fata si din spate is il compara cu o distanta de siguanta.
Deoarece valoarea analogica scrisa pe portul 2 este de zece biti, vom avea:

0-  In cazul in care nici-un obiect nu se afla la o distanta mai mica decat distanta de siguranta;
512 - Un obiect este dincoace de distanta de siguranta, pe partea din spate a dronei!
1023 - Un obiect este dincoace de distanta de siguranta, in pareta frontala a dronei!

Valoarea scrisa in acel pin analogic va fi citita de circuitul ce se ocupa cu semanalizarile luminoase si/sau sonore!
*/

/* --------------- */
//#define DEBUG

#define TINY
//#define MEGA

/* --------------- */

#ifdef MEGA
#define trigPin1 3
#define echoPin1 6

#define trigPin2 4
#define echoPin2 7

#define semnalPin 13
#endif

#ifdef TINY
#define trigPin1 A3 //3
#define echoPin1 0

#define trigPin2 A2 //4
#define echoPin2 1

#define semnalPin A1 //2
#endif

int distantaSiguranta = 80; //Distanta de la care drona incepe sa dea semnale luminoase si/sau sonore!
int BackSensor, FrontSensor;

void setup()
{
	#ifdef DEBUG
		Serial.begin(9600);
	#endif

	pinMode(trigPin1, OUTPUT);
	pinMode(echoPin1, INPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(echoPin2, INPUT);

	pinMode(semnalPin, OUTPUT);
}

void loop()
{
	BackSensor = SonarSensor(trigPin1, echoPin1);
	FrontSensor = SonarSensor(trigPin2, echoPin2);

	if (BackSensor < distantaSiguranta || FrontSensor < distantaSiguranta)
	{
		if (BackSensor < distantaSiguranta && FrontSensor < distantaSiguranta)
			analogWrite(semnalPin, 256);

		if (BackSensor < distantaSiguranta)
			analogWrite(semnalPin, 512);
		else if (FrontSensor < distantaSiguranta)
			analogWrite(semnalPin, 1024);
	}
	else
		analogWrite(semnalPin, 0);

	delay(100);

	#ifdef DEBUG
		Serial.println("Stanga: " + String(BackSensor));
		Serial.println("Dreapta: " + String(FrontSensor));
		Serial.println("");
		delay(600);
	#endif

}

int SonarSensor(int trigPin, int echoPin)
{
	int duration, distance;

	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;

	return distance;
}