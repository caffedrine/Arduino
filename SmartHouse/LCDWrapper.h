/*
 * LCDWrapper.h
 *
 *  Created on: Apr 16, 2019
 *      Author: curiosul
 */

#ifndef LCDWRAPPER_H_
#define LCDWRAPPER_H_

#include <Arduino.h>
#include <LiquidCrystal.h>

class LCD
{
public:
	void Clear()
	{

	}

	void PrintL1(char *str, int len)
	{

	}

	void PrintL2(char *str, int len)
	{

	}

	void Update()
	{

	}
private:
	char _Line1[16] = {''};
	char _Line2[16] = {''};
};

#endif /* LCDWRAPPER_H_ */
