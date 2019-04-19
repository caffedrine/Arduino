/*
 * HC595.h
 *
 *  Created on: Apr 19, 2019
 *      Author: curiosul
 */

#ifndef HC595_H_
#define HC595_H_

#include "HAL.h"
#include "GpioBase.h"

namespace Drivers
{
	class HC595
	{
	public:
		HC595(uint8_t ClockPin, uint8_t DataPin, uint8_t LatchPin, uint8_t RegNo = 1);
		virtual ~HC595();
	private:
		GpioBase _ClockPin, _DataPin, _LatchPin;
		uint8_t _RegNo = 1;

	};

} /* namespace Drivers */

#endif /* HC595_H_ */
