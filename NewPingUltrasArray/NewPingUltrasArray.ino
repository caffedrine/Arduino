#include <NewPing.h>

#define SONAR_NUM     6 			// Number or sensors.
#define MAX_DISTANCE 200 			// Max distance in cm.
#define PING_INTERVAL 33 			// Milliseconds between pings.

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int sensorsDistances[SONAR_NUM]; 		// Store ping distances.
uint8_t currentSensor = 0; 			// Which sensor is active.

/* Sensors identifiers */
typedef enum sensors_ids
{
	FRONT_LEFT_SENSOR	= 0,
	FRONT_MIDDLE_SENSOR	= 1,
	FRONT_RIGHT_SENSOR	= 2,
	BACK_RIGHT_SENSOR	= 3,
	BACK_MIDDLE_SENSOR	= 4,
	BACK_LEFT_SENSOR	= 5
}sensor_id_t;

NewPing sonar[SONAR_NUM] =
{
	//		TR	EC
	NewPing(A0, A1, MAX_DISTANCE),
	NewPing(A2, A3, MAX_DISTANCE),
	NewPing(A4, A5, MAX_DISTANCE),
	NewPing(7, 	6, 	MAX_DISTANCE),
	NewPing(9, 	8, 	MAX_DISTANCE),
    NewPing(11, 10, MAX_DISTANCE)
};

void setup()
{
	Serial.begin(115200);
	pingTimer[0] = millis() + 75; // First ping start in ms.
	for (uint8_t i = 1; i < SONAR_NUM; i++)
		pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop()
{
	for (uint8_t i = 0; i < SONAR_NUM; i++)
	{
		if (millis() >= pingTimer[i])
		{
			pingTimer[i] += PING_INTERVAL * SONAR_NUM;
			if (i == 0 && currentSensor == SONAR_NUM - 1)
				oneSensorCycle(); // Do something with results.
			sonar[currentSensor].timer_stop();
			currentSensor = i;
			sensorsDistances[currentSensor] = 0;
			sonar[currentSensor].ping_timer(echoCheck);
		}
	}

}

void echoCheck()
{
	// If ping echo, set distance to array.
	if (sonar[currentSensor].check_timer())
		sensorsDistances[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle()
{
	static int i = 0;

	Serial.print( i++); Serial.print(".\n");
	Serial.print( sensorsDistances[FRONT_LEFT_SENSOR] ); Serial.print(" ");
	Serial.print( sensorsDistances[FRONT_MIDDLE_SENSOR] ); Serial.print(" ");
	Serial.print( sensorsDistances[FRONT_RIGHT_SENSOR] ); Serial.print("\n");

	Serial.print( sensorsDistances[BACK_LEFT_SENSOR] ); Serial.print(" ");
	Serial.print( sensorsDistances[BACK_MIDDLE_SENSOR] ); Serial.print(" ");
	Serial.print( sensorsDistances[BACK_RIGHT_SENSOR] ); Serial.print("\n\n");
}
