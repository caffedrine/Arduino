/*
 * LedMatrixDriver.h
 *
 *  Created on: Apr 19, 2019
 *      Author: curiosul
 */

#ifndef LedMatrixDriver_H_
#define LedMatrixDriver_H_

#include "HAL.h"
#include "GpioBase.h"
#include "HC595.h"

namespace Drivers
{
	class LedMatrixDriver
	{
	public:
		LedMatrixDriver(uint8_t nCathods, uint8_t nAnods, uint8_t ClockPin, uint8_t DataPin, uint8_t LatchPin);
		virtual ~LedMatrixDriver();

		void SetAll();
		void ClearAll();

		void SetBit(uint8_t x_cathod, uint8_t y_anod);
		void ClearBit(uint8_t c_cathod, uint8_t y_anod);

		void IncrementMatrix();

		void MainFunction();

	private:
		uint8_t _nAnods, _nCathods;
		/* Buffer to store current values */
		uint8_t **_Matrix;
		/* Shift registers used to output the data */
		HC595 *_HC595;
		/* Matrix writing cursor */
		uint8_t _CursorX = 0, _CursorY = 0;

		void SetAllAnodsStates(uint8_t state);
		void SetAllCathodsState(uint8_t state);
		void SetSingleAnodState(uint8_t anod_no, uint8_t state);
		void SetSingleCathodState(uint8_t cathod_no, uint8_t state);
	};

} /* namespace Drivers */

#endif /* LedMatrixDriver_H_ */
