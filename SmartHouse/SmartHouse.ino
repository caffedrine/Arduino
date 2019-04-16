#include <Arduino.h>
#include <X113647Stepper.h>
#include <IRremote.h>
#include <LiquidCrystal.h>

#include "HAL.h"
#include "IR_Codes.h"

#define DEBUG	1

/* LCD config */
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);
/* LCD buffers - empty by default*/
char LCD_Buffer_Line_0[16] = { ' ' };
char LCD_Buffer_Line_1[16] = { ' ' };

/* IR Receiver handlers */
IRrecv irrecv(PIN_IR_RECEIVER);
decode_results results;

/* Motor handler */
X11Stepper motor(PIN_STEPPER_IN1, PIN_STEPPER_IN2, PIN_STEPPER_IN3, PIN_STEPPER_IN4);

/* Helpers */
#define digitalToggle(pin)	digitalWrite(pin, !digitalRead(pin))

/* Globals */
bool MOTION_SENSOR_ENABLED = true;

/* Rooms status (on/off) */
uint8_t RoomsStatusLights[8] = { 0 };

/* Garage door open/close timeout */
unsigned long GarageMillisTimeout = millis();

void setup()
{
	/* Configure OUTPUT pins */
	pinMode(PIN_LIGHT_ROOM_1, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_2, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_3, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_4, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_5, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_6, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_7, OUTPUT);
	pinMode(PIN_LIGHT_ROOM_8, OUTPUT);

	pinMode(PIN_SKELETON_LIGHTS, OUTPUT);
	pinMode(PIN_OUTDOOR_LIGHT, OUTPUT);

	/* Configure INPUT pins */
	pinMode(PIN_PRESENCE_SENSOR, INPUT);
	pinMode(PIN_DAYLIGHT_SENSOR, INPUT);
	pinMode(PIN_IR_RECEIVER, INPUT);

	/* Init IR */
	irrecv.enableIRIn();
	irrecv.blink13(true);

	/* Init LCD  - 16 rows, 2 columns */
	lcd.begin(16, 2);

	/* Init serial for debugging */
	Serial.begin(115200);

	/* Init column 1 with motion detection */
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("   WELCOME TO");
	lcd.setCursor(0, 1);
	lcd.print("  SMART HOUSE!");
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

	if( keyVal == PHONE_IR_CODE_KEY_CH_PLUS || keyVal == RC_IR_CODE_KEY_CH_PLUS )
	{
		GarageMillisTimeout = millis();
		motor.SetDirection(X11Stepper::DIRECTION::FORWARD);
		return;
	}
	else if( keyVal == PHONE_IR_CODE_KEY_CH_MINUS || keyVal == RC_IR_CODE_KEY_CH_MINUS )
	{
		GarageMillisTimeout = millis();
		motor.SetDirection(X11Stepper::DIRECTION::BACKWARD);
		return;
	}

	if( keyVal == PHONE_IR_CODE_KEY_1 || keyVal == RC_IR_CODE_KEY_1 )
	{
		digitalToggle(PIN_LIGHT_ROOM_1);
		RoomsStatusLights[0] = digitalRead(PIN_LIGHT_ROOM_1);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_2 || keyVal == RC_IR_CODE_KEY_2 )
	{
		digitalToggle(PIN_LIGHT_ROOM_2);
		RoomsStatusLights[1] = digitalRead(PIN_LIGHT_ROOM_2);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_3 || keyVal == RC_IR_CODE_KEY_3 )
	{
		digitalToggle(PIN_LIGHT_ROOM_3);
		RoomsStatusLights[2] = digitalRead(PIN_LIGHT_ROOM_3);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_4 || keyVal == RC_IR_CODE_KEY_4 )
	{
		digitalToggle(PIN_LIGHT_ROOM_4);
		RoomsStatusLights[3] = digitalRead(PIN_LIGHT_ROOM_4);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_5 || keyVal == RC_IR_CODE_KEY_5 )
	{
		digitalToggle(PIN_LIGHT_ROOM_5);
		RoomsStatusLights[4] = digitalRead(PIN_LIGHT_ROOM_5);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_6 || keyVal == RC_IR_CODE_KEY_6 )
	{
		digitalToggle(PIN_LIGHT_ROOM_6);
		RoomsStatusLights[5] = digitalRead(PIN_LIGHT_ROOM_6);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_7 || keyVal == RC_IR_CODE_KEY_7 )
	{
		digitalToggle(PIN_LIGHT_ROOM_7);
		RoomsStatusLights[6] = digitalRead(PIN_LIGHT_ROOM_7);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_8 || keyVal == RC_IR_CODE_KEY_8 )
	{
		digitalToggle(PIN_LIGHT_ROOM_8);
		RoomsStatusLights[7] = digitalRead(PIN_LIGHT_ROOM_8);
	}
	else if( keyVal == PHONE_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE || keyVal == RC_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE )
	{
		MOTION_SENSOR_ENABLED = !MOTION_SENSOR_ENABLED;
		digitalWrite(PIN_OUTDOOR_LIGHT, LOW);
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

	memset(LCD_Buffer_Line_0, ' ', sizeof(LCD_Buffer_Line_0));
	sprintf(LCD_Buffer_Line_0, "%s", RoomsStatusLights);

	memset(LCD_Buffer_Line_1, ' ', sizeof(LCD_Buffer_Line_1));
	sprintf(LCD_Buffer_Line_1, "M_detector: %s", MOTION_SENSOR_ENABLED ? "ON" : "OFF");
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
	/* Just exit this task is motion detection is not enabled */
	if( MOTION_SENSOR_ENABLED == false )
	{
		return;
	}

	static int i = 0;
	static bool CurrPresence, PrevPresence;

	CurrPresence = digitalRead(PIN_PRESENCE_SENSOR);
	if( CurrPresence != PrevPresence )
	{
		Serial.print(i++);
		Serial.print(". ");
		PrevPresence = CurrPresence;
		if( CurrPresence == HIGH )
		{
			Serial.println("Presence detected!");
			digitalWrite(PIN_OUTDOOR_LIGHT, HIGH);
		}
		else
		{
			Serial.println("Presence ended!");
			digitalWrite(PIN_OUTDOOR_LIGHT, LOW);
		}
	}
}

void Task_Garage()
{
	static unsigned long PrevStepTimestamp = 0;
	if( millis() - GarageMillisTimeout < 200 )
	{
		if( millis() - PrevStepTimestamp >= 2 )
		{
			PrevStepTimestamp = millis();
			motor.StepNext();
		}
	}
}

void Task_UpdateLcd()
{
	static unsigned long PrevUpdateTimestamp = 0;
	if( millis() - PrevUpdateTimestamp > 50 ) /* 50 Hz frequency should be enough */
	{
		PrevUpdateTimestamp = millis();
		/* Update LCD display every 50ms */
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.write(LCD_Buffer_Line_0, sizeof(LCD_Buffer_Line_0));
		lcd.setCursor(0, 1);
		lcd.write(LCD_Buffer_Line_1, sizeof(LCD_Buffer_Line_1));
	}
}

void loop()
{
	Task_IR();
	Task_MotionDetection();
	Task_Garage();
	Task_UpdateLcd();
}

