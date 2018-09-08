#include <Arduino.h>
#include <NewPing.h>

#include "Motion.h"
#include "TonePlayer.h"

#define BUZZER_PIN		9
#define BUZZER_START_BEEPS_CM	25

#define SAFE_DISTANCE			45
#define MINIMUM_SAFE_DISTANCE	20

#define SONAR_MAX_DISTANCE	200

/* Two basic states */
typedef enum States
{
	MOVE,
	SCAN
}state_t;

/* Scanning states */
typedef enum ScanningStates
{
	FRONT_LEFT,
	FRONT_RIGHT,
	BACK_LEFT,
	BACK_RIGHT
}scan_state_t;

state_t State = States::SCAN;
scan_state_t ScanState = ScanningStates::FRONT_LEFT;

/* Sensors identifiers */
typedef enum sensors_ids
{
	FRONT_LEFT_SENSOR = 0,
	FRONT_MIDDLE_SENSOR = 1,
	FRONT_RIGHT_SENSOR = 2,
	BACK_RIGHT_SENSOR = 3,
	BACK_MIDDLE_SENSOR = 4,
	BACK_LEFT_SENSOR = 5
} sensor_id_t;

/* Sensor data structure */
typedef struct sensor
{
	int echoPin = 0;
	int trigPin = 0;
	int currVal = 0;
	int lastVal = 0;
	int maxDistance = 100;
	//NewPing *driver;
} sensor_t;

/* Sensors array */
sensor_t sensors[6];

/* Initialize buzzer */
TonePlayer buzzer(TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L); // pin D9 (Uno), D11 (Mega)

int GetSensorDistance(int sensor)
{
//	// Classic time consuming method
//	int duration, distance;
//	digitalWrite(sensors[sensor].trigPin, LOW);
//	delayMicroseconds(2);
//	digitalWrite(sensors[sensor].trigPin, HIGH);
//	delayMicroseconds(10);
//	digitalWrite(sensors[sensor].trigPin, LOW);
//	duration = pulseIn(sensors[sensor].echoPin, HIGH);
//	distance = (duration / 2) / 29.1;

	static NewPing sonars[6] =
	        {
	                //		TR	EC
	                //NewPing(sensors[FRONT_LEFT_SENSOR].trigPin, sensors[FRONT_LEFT_SENSOR].echoPin, sensors[FRONT_LEFT_SENSOR].maxDistance),
	                //NewPing(sensors[FRONT_MIDDLE_SENSOR].trigPin, sensors[FRONT_MIDDLE_SENSOR].echoPin, sensors[FRONT_MIDDLE_SENSOR].maxDistance),
	                //NewPing(sensors[FRONT_RIGHT_SENSOR].trigPin, sensors[FRONT_RIGHT_SENSOR].echoPin, sensors[FRONT_RIGHT_SENSOR].maxDistance),
	                NewPing(A0, A1, SONAR_MAX_DISTANCE),
	                NewPing(A2, A3, SONAR_MAX_DISTANCE),
	                NewPing(A4, A5, SONAR_MAX_DISTANCE),
	                NewPing(7, 6, SONAR_MAX_DISTANCE),
	                NewPing(12, 8, SONAR_MAX_DISTANCE),
	                NewPing(11, 10, SONAR_MAX_DISTANCE)
	        };

	int distance = sonars[sensor].ping() / US_ROUNDTRIP_CM;

	/* Also store the distance */
	if( distance > 0 )
	{
		sensors[sensor].lastVal = sensors[sensor].currVal;
		sensors[sensor].currVal = distance;
		return distance;
	}
	else
	{
		return sensors[sensor].currVal;
	}

}

void UpdateSensors()
{
	for (int i = 0; i < (int) (sizeof(sensors) / sizeof(sensors[0])) / 2; i++)
		GetSensorDistance(i);
}

void PrintSensors()
{
	static int i = 0;

	Serial.print(i++);
	Serial.print(".\n");
	Serial.print(sensors[FRONT_LEFT_SENSOR].currVal);
	Serial.print(" ");
	Serial.print(sensors[FRONT_MIDDLE_SENSOR].currVal);
	Serial.print(" ");
	Serial.print(sensors[FRONT_RIGHT_SENSOR].currVal);
	Serial.print("\n");

	Serial.print(sensors[BACK_LEFT_SENSOR].currVal);
	Serial.print(" ");
	Serial.print(sensors[BACK_MIDDLE_SENSOR].currVal);
	Serial.print(" ");
	Serial.print(sensors[BACK_RIGHT_SENSOR].currVal);
	Serial.print("\n\n");
}

void setup()
{
	Serial.begin(115200);

	/* Setting up sensors pins */
	sensors[FRONT_LEFT_SENSOR].echoPin = A1;
	sensors[FRONT_LEFT_SENSOR].trigPin = A0;

	sensors[FRONT_MIDDLE_SENSOR].echoPin = A3;
	sensors[FRONT_MIDDLE_SENSOR].trigPin = A2;

	sensors[FRONT_RIGHT_SENSOR].echoPin = A5;
	sensors[FRONT_RIGHT_SENSOR].trigPin = A4;

	sensors[BACK_LEFT_SENSOR].echoPin = 6;
	sensors[BACK_LEFT_SENSOR].trigPin = 7;

	sensors[BACK_MIDDLE_SENSOR].echoPin = 8;
	sensors[FRONT_MIDDLE_SENSOR].trigPin = 12;

	sensors[BACK_RIGHT_SENSOR].echoPin = 10;
	sensors[FRONT_RIGHT_SENSOR].trigPin = 11;

	/* Initialize pins */
	for (int i = 0; i < (int) (sizeof(sensors) / sizeof(sensors[0])); i++)
	{
		pinMode(sensors[i].echoPin, INPUT);
		pinMode(sensors[i].trigPin, OUTPUT);
	}

	/* Setting up buzzers pins */
	pinMode(BUZZER_PIN, OUTPUT);

	/* Init motors */
	motionInit();
}

int GetMinimumDistance()
{
	int smallest_distance = SONAR_MAX_DISTANCE;
	/* Get smallest distance to check whether buzzes shall send tone or not */
	for (int i = 0; i < (int) (sizeof(sensors) / sizeof(sensors[0])); i++)
	{
		if( (sensors[i].currVal != 0)
		        && (sensors[i].currVal < smallest_distance) )
			smallest_distance = sensors[i].currVal;
	}
	return smallest_distance;
}

int GetMaximumDistance()
{
	int max_distance = 0;
	/* Get smallest distance to check whether buzzes shall send tone or not */
	for (int i = 0; i < (int) (sizeof(sensors) / sizeof(sensors[0])); i++)
	{
		if( (sensors[i].currVal != 0) && (sensors[i].currVal > max_distance) )
			max_distance = sensors[i].currVal;
	}
	return max_distance;
}

bool ClearToGoFront()
{
	if(sensors[FRONT_LEFT_SENSOR].currVal > MINIMUM_SAFE_DISTANCE
					&& sensors[FRONT_RIGHT_SENSOR].currVal > MINIMUM_SAFE_DISTANCE
					&& sensors[FRONT_MIDDLE_SENSOR].currVal > MINIMUM_SAFE_DISTANCE)
		return true;
	else
		return false;
}

bool ClearToGoBack()
{
	if(sensors[BACK_LEFT_SENSOR].currVal > MINIMUM_SAFE_DISTANCE
					&& sensors[BACK_RIGHT_SENSOR].currVal > MINIMUM_SAFE_DISTANCE
					&& sensors[BACK_MIDDLE_SENSOR].currVal > MINIMUM_SAFE_DISTANCE)
		return true;
	else
		return false;
}

long prevMillisUpdateSensors = 0;
long tmpCounter = 0;

void loop()
{
	if( millis() - prevMillisUpdateSensors >= 600 )
	{
		prevMillisUpdateSensors = millis();

		//digitalWrite(FRONT_BUZZER_PIN, HIGH);
		UpdateSensors();
		PrintSensors();

		int smallest_distance = SONAR_MAX_DISTANCE;
		/* Get smallest distance to check whether buzzes shall send tone or not */
		for (int i = 0; i < (int) (sizeof(sensors) / sizeof(sensors[0])); i++)
		{
			if( (sensors[i].currVal != 0) && (sensors[i].currVal < smallest_distance) )
				smallest_distance = sensors[i].currVal;
		}

		if( smallest_distance < BUZZER_START_BEEPS_CM && smallest_distance != 0 )
		{
			int buzzer_hz = map(smallest_distance, 1, BUZZER_START_BEEPS_CM, 10, 1);
			buzzer.tone(buzzer_hz);
		}
		else
		{
			buzzer.noTone();
		}
	}

	/* Car state */
	if(GetMaximumDistance() <= MINIMUM_SAFE_DISTANCE && State != SCAN)
	{
		State = States::SCAN;
		if( sensors[FRONT_LEFT_SENSOR].currVal > sensors[FRONT_RIGHT_SENSOR].currVal )
		{
			ScanState = ScanningStates::FRONT_LEFT;
		}
		else if( sensors[FRONT_RIGHT_SENSOR].currVal > sensors[FRONT_LEFT_SENSOR].currVal )
		{
			ScanState = ScanningStates::FRONT_RIGHT;
		}
	}
	else
	{
		State = States::MOVE;
	}

	/** ********************************************************************************* **/

	/* Handle scanning state */
	if( State == States::SCAN )
	{
		if(sensors[FRONT_LEFT_SENSOR].currVal < MINIMUM_SAFE_DISTANCE
				&& sensors[FRONT_RIGHT_SENSOR].currVal < MINIMUM_SAFE_DISTANCE
				&& sensors[FRONT_MIDDLE_SENSOR].currVal < MINIMUM_SAFE_DISTANCE)
		{
			moveBackward();
		}
		else if( ScanState == ScanningStates::FRONT_LEFT )
		{
			turnLeft();
			if(ClearToGoFront())
				State = States::MOVE;
		}
		else if( ScanState == ScanningStates::FRONT_RIGHT )
		{
			turnRight();
			if(ClearToGoFront())
				State = States::MOVE;
		}
	}

	/* Handle moving state */
	if( State == States::MOVE )
	{
		if( sensors[FRONT_MIDDLE_SENSOR].currVal > SAFE_DISTANCE
		        && sensors[FRONT_LEFT_SENSOR].currVal > SAFE_DISTANCE
		        && sensors[FRONT_RIGHT_SENSOR].currVal > SAFE_DISTANCE )
		{
			moveForward();
		}
		else if( sensors[FRONT_LEFT_SENSOR].currVal > sensors[FRONT_RIGHT_SENSOR].currVal )
		{
			turnLeft();
		}
		else if( sensors[FRONT_RIGHT_SENSOR].currVal > sensors[FRONT_LEFT_SENSOR].currVal )
		{
			turnRight();
		}
	}
}

