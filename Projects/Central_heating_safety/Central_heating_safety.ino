#include "TimerOne\TimerOne.h"
#include "Bounce2\Bounce2.h"
#include <EEPROM.h>

#define testPin 12

/********************************PIN DECLARATION********************************/
// !!!REDUINO COMPATIBLE PINS!!!
//M74HC595 - Shift register

int dataPin = 7;  // D0 - DATA PIN - Pin14  - RCK - ST_CP
int clockPin = 6; // D1 - CLOCK PIN - Pin11 - SCK - SH_CP
int latchPin = 2; // D2 - LATCH PIN - Pin12 - DS

/*
// Only for debuging MEGA 2560 - Now working with define!!!
int latchPin = 8; //ST_CP - Storage register clock pin - latch pin - RCK
int clockPin = 9;   //SH_CP - Shift register clock pin - SCK
int dataPin = 10;  //DS - Serial DATA pin - DS
*/

//Button - Switch display (show live temperatures from sensors OR limit seted temperatuser from memory)
//5V applied on button push
#define switchDisplayButton 4 //D4

//Pins for sensors - analogic pins
#define ambSenzPin A6   // Ambiental temperature sensor
#define centrSenzPin A7 // Central heating temperature sensor

//Menu buttons pins - 5v applied on push
#define incrementButtonPin A0  //increment temperature limit on push
#define decrementButtonPin A1  //decrement temperature limit on push
#define selAmbTempButtonPin A2 //select ambiental temperature
#define selCenTempButtonPin A4 //select heating central temperature

//LEDs pins
#define ambSelLed A3   //LEd ON when ambiental temperature is displayed
#define centSelLed A5  //LED is on when central heating temperature is displayed
#define alertLed 3     //D3 - when central heating temperature is more than limit
#define tmpLiveLed 5   //D5 - LED is on when temperature from sensors is displayed

#define relayPin 13 //D13
/*******************************END PIN DECLARATION******************************/

//Initial configurationon
// Maximum limits
int centrTempLimit = 85; // Maximum heating central temperature limit
int ambTempLimit = 35;  // Maximum ambientaltemperature limit
int cntAddr = 0; //Store these values on EPROM so
int ambAddr = 1; //we can retrieve settings after power off


// Current temperatures variables
int currCentrTemp;
int currAmbTemp;

// Need only two declarations, whene these are false the others (show strored temp and amb temp) are true
bool displayLiveTemp = true; // Show live temperatures from sensors when true
bool displayCentrTemp = true; // Show heating central temperature when true
bool setTmp = false;

// Numbers from 0 to 9 for digits
int digitOne[10] = { 64, 121, 164, 48, 25, 18, 2, 120, 128, 144 };

Bounce dispBouncer = Bounce();
Bounce ambBouncer = Bounce();
Bounce cntBouncer = Bounce();
Bounce incBouncer = Bounce();
Bounce decBouncer = Bounce();

void setup()
{
	if (EEPROM.read(cntAddr) > 10 && EEPROM.read(cntAddr) < 99)
		centrTempLimit = EEPROM.read(cntAddr);

	if (EEPROM.read(ambAddr) > 10 && EEPROM.read(ambAddr) < 99)
		ambTempLimit = EEPROM.read(ambAddr);

	//Using this pin only to test if program works properly and were uploaded on chip
	pinMode(testPin, OUTPUT);

	pinMode(ambSelLed, OUTPUT);
	pinMode(centSelLed, OUTPUT);
	pinMode(alertLed, OUTPUT);
	pinMode(tmpLiveLed, OUTPUT);

	pinMode(switchDisplayButton, INPUT_PULLUP);
	pinMode(incrementButtonPin, INPUT_PULLUP);
	pinMode(decrementButtonPin, INPUT_PULLUP);
	pinMode(selAmbTempButtonPin, INPUT_PULLUP);
	pinMode(selCenTempButtonPin, INPUT_PULLUP);

	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);

	pinMode(relayPin, OUTPUT);
	digitalWrite(relayPin, LOW); //Power off initially, open relay only if restrictions are respected

	updateTmp(); //getting initial temperature
	setNumber(0);//set display initially to 0

	//Not allowed o uno, we do not have interrupt on this pin.
	//Setting up timer1 to read sensors every 1 second
	//Timer1.initialize(1.5e6);			//read sensors temperature every 1.5 seconds
	//Timer1.attachInterrupt(t1Callback); 

	dispBouncer.attach(switchDisplayButton);
	ambBouncer.attach(selAmbTempButtonPin);
	cntBouncer.attach(selCenTempButtonPin);
	incBouncer.attach(incrementButtonPin);
	decBouncer.attach(decrementButtonPin);

	dispBouncer.interval(5);
	ambBouncer.interval(5);
	cntBouncer.interval(5);
	incBouncer.interval(300);
	decBouncer.interval(300);
}

unsigned long interval = 1000; // read temperature every 1 seconds
unsigned long previousMillis = 0; // millis() returns an unsigned long.

#define NUM_READS 100 //used to estompate the noise from sensors


void loop()
{
	
	//No interruption supported on all button pins, so we have to deal with main loop :)
	dispBouncer.update();
	ambBouncer.update();
	cntBouncer.update();
	incBouncer.update();
	decBouncer.update();

	//update temp every interval
	unsigned long currentMillis = millis();
	if ((currentMillis - previousMillis) > interval)
	{
		digitalWrite(testPin, !digitalRead(testPin));
		updateTmp();
		currentMillis = 0;
		previousMillis = millis();
	}

	int disp = dispBouncer.read();
	int amb = ambBouncer.read();
	int cnt = cntBouncer.read();
	int inc = incBouncer.read();
	int dec = decBouncer.read();
	
	//If temperature from sensors is highter than limit, do what you have to do
	if (currAmbTemp > ambTempLimit || currCentrTemp > centrTempLimit)
		setRelay(false);
	else if (currAmbTemp < ambTempLimit - 4 && currCentrTemp < centrTempLimit - 7)
		setRelay(true);
	
	/* //Display test
	for (int i = 0; i <= 99; i++)
	{
		setNumber(i);
		makeTest();
		delay(500);
	}
	*/
	/* //Sensors test, good for debuging
	Serial.write("Amb tmp: "); Serial.println(currAmbTemp);
	Serial.write("Cnt tmp: "); Serial.println(currCentrTemp);
	Serial.println();

	delay(1000);
	*/
	
	if (disp == HIGH)
	{
		displayLiveTemp = !displayLiveTemp;
		delay(250);
	}

	if (amb == HIGH)
		displayCentrTemp = false;

	if (cnt == HIGH)
		displayCentrTemp = true;

	if (inc == HIGH)
	{
		tempIncrement();
		delay(500);
	}

	if (dec == HIGH)
	{
		tempDecrement();
		delay(500);
	}

	updateDisplay();
	/*//Debuging buttons
	setLiveTempLed(getBoolFromDigital(disp));
	setCentrDisplayLed( getBoolFromDigital( cnt ));
	setAmbDisplayLed( getBoolFromDigital( amb ));*/	
}

void loopdbg()
{
	for (int i = 0; i <= 99; i++)
	{
		setNumber(i);
		delay(500);
	}
}

void makeTest()
{
	setCentrDisplayLed( !digitalRead(centSelLed) );
	setAmbDisplayLed( !digitalRead(ambSelLed) );
	setLiveTempLed( !digitalRead(tmpLiveLed));
	setAlertLed( !digitalRead(alertLed));
	setRelay( !digitalRead(relayPin) );

	//or
	/*
	setLiveTempLed(digitalRead(switchDisplayButton));
	setCentrDisplayLed(digitalRead(selCenTempButtonPin));
	setAmbDisplayLed(digitalRead(selAmbTempButtonPin));
	*/
}

void updateTmp()
{
	currCentrTemp = convertTemp(analogRead(centrSenzPin)) - 5;
	currAmbTemp = convertTemp(analogRead(ambSenzPin));
	//currCentrTemp = readTemperature(centrSenzPin);
	//currAmbTemp = readTemperature(centrSenzPin) ;
}

void updateDisplay()
{
	delay(10);

	if (displayLiveTemp == true)
	{
		setLiveTempLed(true);

		if (displayCentrTemp == true)
		{
			setCentrDisplayLed(true);
			setAmbDisplayLed(false);
			setNumber(currCentrTemp);
		}
		else
		{
			setCentrDisplayLed(false);
			setAmbDisplayLed(true);
			setNumber(currAmbTemp);
		}
	}
	else
	{
		setLiveTempLed(false);

		if (displayCentrTemp == true)
		{
			setCentrDisplayLed(true);
			setAmbDisplayLed(false);
			setNumber(centrTempLimit);
		}
		else
		{
			setCentrDisplayLed(false);
			setAmbDisplayLed(true);
			setNumber(ambTempLimit);
		}
	}
}

void tempDecrement()
{
	if (displayLiveTemp == false)
	{
		if (displayCentrTemp == true)
		{
			if (centrTempLimit > 1)
			{
				centrTempLimit--;
				EEPROM.write(cntAddr, centrTempLimit);
			}
		}
		else
		{
			if (ambTempLimit > 1)
			{
				ambTempLimit--;
				EEPROM.write(ambAddr, ambTempLimit);
			}
		}
	}
}

void tempIncrement()
{
	if (displayLiveTemp == false)
	{
		if (displayCentrTemp == true)
		{
			if (centrTempLimit < 99)
			{
				centrTempLimit++;
				EEPROM.write(cntAddr, centrTempLimit);
			}
		}
		else
		{
			if (ambTempLimit < 99)
			{
				ambTempLimit++;
				EEPROM.write(ambAddr, ambTempLimit);
			}
		}
	}
}

void setRelay(bool state)
{
	if (state)
		digitalWrite(relayPin, HIGH);
	else
		digitalWrite(relayPin, LOW);

	setAlertLed(!state);
}

void setCentrDisplayLed(bool state)
{
	if (state)
		digitalWrite(centSelLed, HIGH);
	else
		digitalWrite(centSelLed, LOW);
}

void setAmbDisplayLed(bool state)
{
	if (state)
		digitalWrite(ambSelLed, HIGH);
	else
		digitalWrite(ambSelLed, LOW);
}

void setLiveTempLed(bool state)
{
	if (state)
		digitalWrite(tmpLiveLed, HIGH);
	else
		digitalWrite(tmpLiveLed, LOW);
}

void setAlertLed(bool state)
{
	if (state)
		digitalWrite(alertLed, HIGH);
	else
		digitalWrite(alertLed, LOW);
}

void setNumber(int number)
{
	//function to set a number to display from 0 to 99
	int unitati = 0;
	int zeci = 0;

	if (number > 99)
	{
		unitati = 9;
		zeci = 9;
	}
	else if (number < 10)
	{
		unitati = number;
		zeci = 0;
	}
	else
	{
		zeci = number / 10;
		unitati = number % 10;
	}

	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, digitOne[zeci]);
	shiftOut(dataPin, clockPin, MSBFIRST, digitOne[unitati]);
	digitalWrite(latchPin, HIGH);
}

bool getBoolFromDigital(int digit)
{
	if (digit == HIGH)
		return true;
	else
		return false;
}

int convertTemp(int analogicRead)
{
	//return ((analogicRead * 0.004882814) - 0.5) * 100.0;
	float voltage = analogicRead * 5.0;
	voltage /= 1024.0;
	
	float temperatureC = (voltage - 0.5) * 100;

	return temperatureC;
}

float readTemperature(int sensorpin)
{
	// read multiple values and sort them to take the mode
	int sortedValues[NUM_READS];
	for (int i = 0; i<NUM_READS; i++)
	{
		int value = analogRead(sensorpin);
		int j;
		if (value<sortedValues[0] || i == 0)
		{
			j = 0; //insert at first position
		}
		else
		{
			for (j = 1; j<i; j++)
			{
				if (sortedValues[j - 1] <= value && sortedValues[j] >= value){

					// j is insert position
					break;
				}
			}
		}
		for (int k = i; k>j; k--){
			// move all values higher than current reading up one position
			sortedValues[k] = sortedValues[k - 1];
		}
		sortedValues[j] = value; //insert current reading
	}
	//return scaled mode of 10 values
	float returnval = 0;
	for (int i = NUM_READS / 2 - 5; i<(NUM_READS / 2 + 5); i++)
	{
		returnval += sortedValues[i];
	}
	returnval = returnval / 10;
	return returnval * 1100 / 1023;
}


