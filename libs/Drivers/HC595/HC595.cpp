/*
 * HC595.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: curiosul
 */

#include "HC595.h"

namespace Drivers
{

	HC595::HC595(uint8_t ClockPin, uint8_t DataPin, uint8_t LatchPin, uint8_t RegNo) : _ClockPin(ClockPin, OUTPUT), _DataPin(DataPin, OUTPUT), _LatchPin(LatchPin, OUTPUT), _RegNo(RegNo)
	{
	}

	HC595::~HC595()
	{
	}

} /* namespace Drivers */
