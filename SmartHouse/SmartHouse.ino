#include "Arduino.h"

#include <IRremote.h>
#include <LiquidCrystal.h>

/* PINS MAPPING */
#define PIN_LIGHT_ROOM_1			28
#define	PIN_LIGHT_ROOM_2			29
#define PIN_LIGHT_ROOM_3			30
#define	PIN_LIGHT_ROOM_4			31
#define PIN_LIGHT_ROOM_5			32
#define	PIN_LIGHT_ROOM_6			33
#define PIN_LIGHT_ROOM_7			34
#define	PIN_LIGHT_ROOM_8			35

#define PIN_STEPPER_IN1				8
#define PIN_STEPPER_IN2				9
#define PIN_STEPPER_IN3				10
#define PIN_STEPPER_IN4				11

#define PIN_LCD_D4					24
#define PIN_LCD_D5					25
#define PIN_LCD_D6					26
#define PIN_LCD_D7					27
#define PIN_LCD_RS					22
#define PIN_LCD_EN					23

#define PIN_SKELETON_LIGHTS			38

#define PIN_PRESENCE_SENSOR			3
#define PIN_DAYLIGHT_SENSOR			40
#define PIN_IR_RECEIVER				12
#define PIN_OUTDOOR_LIGHT			51

/* IR Codes */
#define PHONE_IR_CODE_KEY_0			3772811383
#define PHONE_IR_CODE_KEY_1			3772784863
#define PHONE_IR_CODE_KEY_2			3772817503
#define PHONE_IR_CODE_KEY_3			3772801183
#define PHONE_IR_CODE_KEY_4			3772780783
#define PHONE_IR_CODE_KEY_5			3772813423
#define PHONE_IR_CODE_KEY_6			3772797103
#define PHONE_IR_CODE_KEY_7			3772788943
#define PHONE_IR_CODE_KEY_8			3772821583
#define PHONE_IR_CODE_KEY_9			3772805263
#define PHONE_IR_CODE_KEY_YELLOW	3772819543
#define PHONE_IR_CODE_KEY_BLUE		3772803223
#define PHONE_IR_CODE_KEY_RED		3772790473
#define PHONE_IR_CODE_KEY_GREEN		3772786903
#define PHONE_IR_CODE_KEY_PLUS		3772833823
#define PHONE_IR_CODE_KEY_MINUS		3772829743
#define PHONE_IR_CODE_KEY_CH_PLUS	3772795063
#define PHONE_IR_CODE_KEY_CH_MINUS	3772778743
#define PHONE_IR_CODE_KEY_POWER		3772793023
#define PHOME_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE	3772816993

#define RC_IR_CODE_KEY_0			109562876
#define RC_IR_CODE_KEY_1			109562864
#define RC_IR_CODE_KEY_2			109562824
#define RC_IR_CODE_KEY_3			109562856
#define RC_IR_CODE_KEY_4			109562872
#define RC_IR_CODE_KEY_5			109562820
#define RC_IR_CODE_KEY_6			109562852
#define RC_IR_CODE_KEY_7			109562868
#define RC_IR_CODE_KEY_8			109562828
#define RC_IR_CODE_KEY_9			109562860
#define RC_IR_CODE_KEY_YELLOW		109562822
#define RC_IR_CODE_KEY_BLUE			109562832
#define RC_IR_CODE_KEY_RED			109562838
#define RC_IR_CODE_KEY_GREEN		109562870
#define RC_IR_CODE_KEY_PLUS			109562874
#define RC_IR_CODE_KEY_MINUS		109562826
#define RC_IR_CODE_KEY_CH_PLUS		109562834
#define RC_IR_CODE_KEY_CH_MINUS		109562866
#define RC_IR_CODE_KEY_POWER		109562816
#define RC_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE	109562844

/* IR Receiver handlers */
IRrecv irrecv(PIN_IR_RECEIVER);
decode_results results;

/* LCD config */
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

/* Helpers */
#define digitalToggle(pin)	digitalWrite(pin, !digitalRead(pin))

/* Globals */
bool MOTION_SENSOR_ENABLED = true;

/* Rooms status (on/off) */
uint8_t RoomsStatusLights[8] = {0};

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

	pinMode(PIN_STEPPER_IN1, OUTPUT);
	pinMode(PIN_STEPPER_IN2, OUTPUT);
	pinMode(PIN_STEPPER_IN3, OUTPUT);
	pinMode(PIN_STEPPER_IN4, OUTPUT);

	pinMode(PIN_LCD_D4, OUTPUT);
	pinMode(PIN_LCD_D5, OUTPUT);
	pinMode(PIN_LCD_D6, OUTPUT);
	pinMode(PIN_LCD_D7, OUTPUT);
	pinMode(PIN_LCD_RS, OUTPUT);
	pinMode(PIN_LCD_EN, OUTPUT);

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
	Serial.begin(9600);

	/* Init column 1 with motion detection */
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("   WELCOME TO");
	lcd.setCursor(0, 1);
	lcd.print("  SMART HOUSE!");
}

void loop()
{
	Task_IR();
	Task_MotionDetection();
}


void onIrKeyRecv(unsigned long keyVal)
{
	/* Debouncing buttons presses */
	static unsigned long PrevMillis = 0;
	if (millis() - PrevMillis >= 100)
	{
		PrevMillis = millis();
	}
	else
	{
		return;
	}

	static int i = 0;
	Serial.print(i++);
	Serial.print(". IR recv: ");
	Serial.println(keyVal);

	if (keyVal == PHONE_IR_CODE_KEY_1 || keyVal == RC_IR_CODE_KEY_1)
	{
		digitalToggle(PIN_LIGHT_ROOM_1);
		RoomsStatusLights[0] = digitalRead(PIN_LIGHT_ROOM_1);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_2 || keyVal == RC_IR_CODE_KEY_2)
	{
		digitalToggle(PIN_LIGHT_ROOM_2);
		RoomsStatusLights[1] = digitalRead(PIN_LIGHT_ROOM_2);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_3 || keyVal == RC_IR_CODE_KEY_3)
	{
		digitalToggle(PIN_LIGHT_ROOM_3);
		RoomsStatusLights[2] = digitalRead(PIN_LIGHT_ROOM_3);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_4 || keyVal == RC_IR_CODE_KEY_4)
	{
		digitalToggle(PIN_LIGHT_ROOM_4);
		RoomsStatusLights[3] = digitalRead(PIN_LIGHT_ROOM_4);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_5 || keyVal == RC_IR_CODE_KEY_5)
	{
		digitalToggle(PIN_LIGHT_ROOM_5);
		RoomsStatusLights[4] = digitalRead(PIN_LIGHT_ROOM_5);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_6 || keyVal == RC_IR_CODE_KEY_6)
	{
		digitalToggle(PIN_LIGHT_ROOM_6);
		RoomsStatusLights[5] = digitalRead(PIN_LIGHT_ROOM_6);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_7 || keyVal == RC_IR_CODE_KEY_7)
	{
		digitalToggle(PIN_LIGHT_ROOM_7);
		RoomsStatusLights[6] = digitalRead(PIN_LIGHT_ROOM_7);
	}
	else if (keyVal == PHONE_IR_CODE_KEY_8 || keyVal == RC_IR_CODE_KEY_8)
	{
		digitalToggle(PIN_LIGHT_ROOM_8);
		RoomsStatusLights[7] = digitalRead(PIN_LIGHT_ROOM_8);
	}
	else if( keyVal == PHOME_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE || keyVal == RC_IR_CODE_KEY_OUTDOOR_LIGHTS_ENABLE )
	{
		MOTION_SENSOR_ENABLED = !MOTION_SENSOR_ENABLED;
		digitalWrite(PIN_OUTDOOR_LIGHT, LOW);
		Serial.print("Motion detection: ");
		Serial.println(((MOTION_SENSOR_ENABLED)?("ENABLED"):("DISABLED")));
	}

	String buffer = "";
	for(int i = 0; i < 8; i++)
	{
		if( RoomsStatusLights[i] == 0 )
			buffer += "/";
		else
			buffer += "0";
		buffer += " ";
	}

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(buffer);

	lcd.setCursor(0, 1);
	if(MOTION_SENSOR_ENABLED)
		lcd.print("M_detector: ON");
	else
		lcd.print("M_detector: OFF");
}

void Task_IR()
{
	/* Process IR received command */
	if (irrecv.decode(&results))
	{
		onIrKeyRecv(results.value);
		irrecv.resume();
	}
}

void Task_MotionDetection()
{
	/* Just exit this task is motion detection is not enabled */
	if (MOTION_SENSOR_ENABLED == false)
	{
		return;
	}

	static int i = 0;
	static bool CurrPresence, PrevPresence;

	CurrPresence = digitalRead(PIN_PRESENCE_SENSOR);
	if (CurrPresence != PrevPresence)
	{
		Serial.print(i++);
		Serial.print(". ");
		PrevPresence = CurrPresence;
		if(CurrPresence == HIGH)
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

