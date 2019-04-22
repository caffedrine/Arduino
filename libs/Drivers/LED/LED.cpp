/*
 * LED.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: curiosul
 */

#include "LED.h"

namespace Drivers
{

	LED::LED(uint8_t Pin) : _Pin(Pin)
	{
		this->Off();
	}

	LED::~LED()
	{
		this->Off();
	}

	void LED::On()
	{
		Vfb_DigitalWrite(this->_Pin, HIGH);
	}

	void LED::Off()
	{
		Vfb_DigitalWrite(this->_Pin, LOW);
	}

	void LED::Toggle()
	{
		Vfb_DigitalToggle(this->_Pin);
	}

	LED::STATE LED::GetState()
	{
		if( Vfb_DigitalRead(this->_Pin) == HIGH )
		{
			return LED::STATE::ON;
		}
		else
		{
			return LED::STATE::OFF;
		}
	}

} /* namespace Drivers */
