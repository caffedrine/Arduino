#include <Arduino.h>
#include <X113647Stepper.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <LED.h>
#include <BasicLCD.h>
#include <GpioBase.h>

#include "IR_Codes.h"
#include "PinMap.h"

#define DEBUG	1

using namespace Drivers;

/* LCD config */
BasicLCD lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

/* IR Receiver handlers */
IRrecv irrecv(PIN_IR_RECEIVER);
decode_results results;

/* Motor handler */
X11Stepper motor(PIN_STEPPER_IN1, PIN_STEPPER_IN2, PIN_STEPPER_IN3, PIN_STEPPER_IN4);
bool MotorInitialized = false;

/* Globals */
bool MOTION_SENSOR_ENABLED = false;

/* rooms handlers */
LED Room1(PIN_LIGHT_ROOM_1);
LED Room2(PIN_LIGHT_ROOM_2);
LED Room3(PIN_LIGHT_ROOM_3);
LED Room4(PIN_LIGHT_ROOM_4);
LED Room5(PIN_LIGHT_ROOM_5);
LED Room6(PIN_LIGHT_ROOM_6);
LED Room7(PIN_LIGHT_ROOM_7);
LED Room8(PIN_LIGHT_ROOM_8);

/* Other GPIO handlers */
LED SkeletonLight(PIN_SKELETON_LIGHTS);
LED OutdoorLight(PIN_OUTDOOR_LIGHT);
GpioBase PresenceSensor(PIN_PRESENCE_SENSOR, INPUT);
GpioBase DaylightSensor(PIN_DAYLIGHT_SENSOR, INPUT);

/* Garage door open/close timeout */
unsigned long GarageMillisTimeout = millis();

void setup()
{
	/* Init serial for debugging */
	Serial.begin(115200);

	/* Init IR */
	irrecv.enableIRIn();
	irrecv.blink13(true);

	/* Init LCD  - 16 rows, 2 columns */
	lcd.Init(16, 2);

	/* Init column 1 with motion detection */
	lcd.PrintLine("   WELCOME TO", 0);
	lcd.PrintLine("  SMART HOUSE!", 1);

	/* Timer5 for uniform motor movement */
	noInterrupts();
	TCCR3A = 0;
	TCCR3B = 0;
	TCNT3 = 60000;            // preload timer 65536-16MHz/256/2Hz
	TCCR3B |= (1 << CS11);    // 256 prescaler
	TIMSK3 |= (1 << TOIE1);   // enable timer overflow interrupt
	interrupts();
}

void onIrKeyRecv(unsigned long keyVal)
{
	/* Debouncing buttons presses */
	static unsigned long LastKey = 0;
	static const unsigned int IR_DEBOUNCING_MS = 150;
	static unsigned long PrevMillis = 0;
	if( millis() - PrevMillis >= IR_DEBOUNCING_MS )
	{
		PrevMillis = millis();
	}
	else
	{
		return;
	}

	/* Is it the last key which continues to be presses? */
	if( keyVal == PHONE_IR_CODE_KEY_LAST || keyVal == RC_IR_CODE_KEY_LAST )
	{
		keyVal = LastKey;
	}
	else
	{
		LastKey = keyVal;
	}

	#if DEBUG == 1
		Serial.print("IR recv: ");
		Serial.println(keyVal);
	#endif

	if( keyVal == PHONE_IR_CODE_KEY_PLUS || keyVal == RC_IR_CODE_KEY_PLUS )
	{
		GarageMillisTimeout = millis();
		MotorInitialized = true;
		motor.SetDirection(X11Stepper::DIRECTION::BACKWARD);
		return;
	}
	else if( keyVal == PHONE_IR_CODE_KEY_MINUS || keyVal == RC_IR_CODE_KEY_MINUS )
	{
		GarageMillisTimeout = millis();
		MotorInitialized = true;
		motor.SetDirection(X11Stepper::DIRECTION::FORWARD);
		return;
	}

	if( keyVal == PHONE_IR_CODE_KEY_1 || keyVal == RC_IR_CODE_KEY_1 )
	{
		Room1.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_2 || keyVal == RC_IR_CODE_KEY_2 )
	{
		Room2.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_3 || keyVal == RC_IR_CODE_KEY_3 )
	{
		Room3.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_4 || keyVal == RC_IR_CODE_KEY_4 )
	{
		Room4.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_5 || keyVal == RC_IR_CODE_KEY_5 )
	{
		Room5.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_6 || keyVal == RC_IR_CODE_KEY_6 )
	{
		Room6.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_7 || keyVal == RC_IR_CODE_KEY_7 )
	{
		Room7.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_8 || keyVal == RC_IR_CODE_KEY_8 )
	{
		Room8.Toggle();
	}
	else if( keyVal == PHONE_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE || keyVal == RC_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE )
	{
		MOTION_SENSOR_ENABLED = !MOTION_SENSOR_ENABLED;
		OutdoorLight.Off();

		#if DEBUG == 1
				Serial.print("Motion detection: ");
				Serial.println(((MOTION_SENSOR_ENABLED) ? ("ENABLED") : ("DISABLED")));
		#endif
	}
	else
	{
		/* Do not debounce invalid codes */
		PrevMillis -= (IR_DEBOUNCING_MS + 1);
		return;
	}

	#if DEBUG == 1
		static int i = 0;
		Serial.print(i++);
		Serial.print(". IR recv: ");
		Serial.println(keyVal);
	#endif

	/* Print data to display */
	String RoomsStatusStr = "";
	RoomsStatusStr += ( (Room1.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room2.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room3.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room4.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room5.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room6.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room7.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	RoomsStatusStr += ( (Room8.GetState() == LED::STATE::ON)?("1 "):("0 ") );
	lcd.PrintLine( RoomsStatusStr, 0);

	if(MOTION_SENSOR_ENABLED == true)
		lcd.PrintLine("M_detector: ON", 1);
	else
		lcd.PrintLine("M_detector: OFF", 1);
}

void Task_IR()
{
	/* Process IR received command */
	if( irrecv.decode(&results) )
	{
		onIrKeyRecv(results.value);
		irrecv.resume();
	}
}

void Task_MotionDetection()
{
	/* Just exit this task if motion detection is not enabled */
	if( MOTION_SENSOR_ENABLED == false )
	{
		return;
	}

	static int i = 0;
	static bool CurrPresence, PrevPresence;

	CurrPresence = PresenceSensor.Read();
	if( CurrPresence != PrevPresence )
	{
		Serial.print(i++);
		Serial.print(". ");
		PrevPresence = CurrPresence;
		if( CurrPresence == HIGH )
		{
			#if DEBUG == 1
				Serial.println("Presence detected!");
			#endif
			lcd.PrintLine("Presence started!", 1);
			OutdoorLight.On();
		}
		else
		{
			#if DEBUG == 1
				Serial.println("Presence ended!");
			#endif
			OutdoorLight.Off();
			lcd.PrintLine("Presence ended!", 1);
		}
	}
}

void Task_Garage()
{
	if( !MotorInitialized)
		return;

	static unsigned long PrevStepTimestamp =  millis();
	if( millis() - GarageMillisTimeout < 300 )
	{
		if( millis() - PrevStepTimestamp >= 2 )
		{
			PrevStepTimestamp = millis();
			motor.StepNext();
		}
	}
	else
	{
		motor.Stop();
	}
}

ISR(TIMER3_OVF_vect)
{
	TCNT3 = 60000;            // preload timer
	Task_Garage();
}

void loop()
{
	Task_IR();
	Task_MotionDetection();
	lcd.Update();
}

