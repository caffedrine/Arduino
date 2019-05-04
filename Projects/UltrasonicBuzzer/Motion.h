/*
 * Motion.h
 *
 *  Created on: Sep 8, 2018
 *      Author: curiosul
 */

#ifndef MOTION_H_
#define MOTION_H_

#include <Arduino.h>

int DrFr = 3;
int DrSp = 2;
int StFr = 4;
int StSp = 5;

void motionInit()
{
	pinMode(DrFr,OUTPUT);
	pinMode(StFr,OUTPUT);
	pinMode(DrSp,OUTPUT);
	pinMode(StSp,OUTPUT);
	digitalWrite(DrFr,LOW);
	digitalWrite(StFr,LOW);
	digitalWrite(DrSp,LOW);
	digitalWrite(StSp,LOW);
}

void moveStop()
{
	digitalWrite(DrFr, LOW);
	digitalWrite(StFr, LOW);
	digitalWrite(DrSp, LOW);
	digitalWrite(StSp, LOW);
}

void moveBackward()
{
	digitalWrite(DrFr, HIGH);
	digitalWrite(StFr, HIGH);
	digitalWrite(DrSp, LOW);
	digitalWrite(StSp, LOW);
}

void moveForward()
{
	digitalWrite(DrFr, LOW);
	digitalWrite(StFr, LOW);
	digitalWrite(DrSp, HIGH);
	digitalWrite(StSp, HIGH);
}

void turnLeft()
{
	digitalWrite(DrFr, LOW);
	digitalWrite(StFr, HIGH);
	digitalWrite(DrSp, HIGH);
	digitalWrite(StSp, LOW);
}

void turnRight()
{
	digitalWrite(DrFr, HIGH);
	digitalWrite(StFr, LOW);
	digitalWrite(DrSp, LOW);
	digitalWrite(StSp, HIGH);
}

#endif /* MOTION_H_ */
