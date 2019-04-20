/*
 * TestHC595.h
 *
 *  Created on: Apr 20, 2019
 *      Author: curiosul
 */

#ifndef TESTHC595_H_
#define TESTHC595_H_

#include "Arduino.h"

#include "GpioBase.h"
#include "HC595.h"

using namespace Drivers;

GpioBase led(13, OUTPUT);
HC595 reg(2, 3, 4, 2);

void setup()
{
	Serial.begin(115200);
	reg.ClearAll();
}

void loop()
{
	led.Toggle();

	uint8_t data[2];
	data[0] = 0b01010101;
	data[1] = 0b10101010;
	reg.WriteRaw(data, 2);
	reg.Update();

	delay(50);
}

#endif /* TESTHC595_H_ */
