/*
 * LedMatrixDriver.cpp
 *
 *  Created on: Apr 19, 2021
 *      Author: curiosul
 */

#include "LedMatrixDriver.h"

namespace Drivers
{

	LedMatrixDriver::LedMatrixDriver(uint8_t nCathods, uint8_t nAnods, uint8_t ClockPin, uint8_t DataPin, uint8_t LatchPin)
	{
		this->_nCathods = nCathods;
		this->_nAnods = nAnods;

		this->_Matrix = (uint8_t **)malloc((this->_nCathods)*sizeof(uint8_t *));
		for( int i = 0; i < this->_nAnods; i++ )
		{
			this->_Matrix[i] = (uint8_t *)malloc(this->_nAnods * sizeof(uint8_t));
		}

		this->_HC595 = new HC595(ClockPin, DataPin, LatchPin, ((this->_nCathods+this->_nAnods)/8) + ((((this->_nCathods+this->_nAnods)%8)>0)?(1):(0)) );
	}

	LedMatrixDriver::~LedMatrixDriver()
	{
		for( int i = 0; i < this->_nAnods; i++ )
		{
			free((void *)this->_Matrix[i]);
		}
		free(this->_Matrix);

		delete(this->_HC595);
	}

	void LedMatrixDriver::SetAll()
	{
		memset(this->_Matrix, 1, (this->_nCathods*this->_nAnods)*sizeof(uint8_t));
	}

	void LedMatrixDriver::ClearAll()
	{
		memset(this->_Matrix, 0, (this->_nCathods*this->_nAnods)*sizeof(uint8_t));
	}

	void LedMatrixDriver::SetBit(uint8_t x_cathod, uint8_t y_anod)
	{
		this->_Matrix[x_cathod, y_anod] = 1;
	}

	void LedMatrixDriver::ClearBit(uint8_t x_cathod, uint8_t y_anod)
	{
		this->_Matrix[x_cathod, y_anod] = 0;
	}

	void LedMatrixDriver::IncrementMatrix()
	{

	}

	void LedMatrixDriver::MainFunction()
	{
		// Remove all current values from shift register
		this->SetAllAnodsStates(LOW);
		this->SetAllCathodsState(HIGH);

		this->SetSingleAnodState(this->_CursorX++, HIGH);
		if( this->_CursorX >= this->_nAnods )
			this->_CursorX = 0;

		this->SetSingleCathodState(0, LOW);
		this->SetSingleCathodState(1, LOW);
//		this->SetSingleCathodState(this->_CursorY++, LOW);
//		if( this->_CursorY >= this->_nCathods - 1 )
//			this->_CursorY = 0;

		// Trigger shift registers main function to send data to output
		this->_HC595->MainFunction();

	}

	void LedMatrixDriver::SetAllAnodsStates(uint8_t state)
	{
		if( state == HIGH )
		{
			this->_HC595->SetFirstNBits(this->_nAnods);
		}
		else
		{
			this->_HC595->ClearFirstNBits(this->_nAnods);
		}
	}
	void LedMatrixDriver::SetAllCathodsState(uint8_t state)
	{
		if( state == HIGH )
		{
			this->_HC595->SetLastNBits(this->_nCathods);
		}
		else
		{
			this->_HC595->ClearLastNBits(this->_nCathods);
		}
	}
	void LedMatrixDriver::SetSingleAnodState(uint8_t anod_no, uint8_t state)
	{
		if( state == HIGH )
		{
			this->_HC595->SetBitNo( anod_no );
		}
		else
		{
			this->_HC595->ClearBitNo( anod_no );
		}
	}
	void LedMatrixDriver::SetSingleCathodState(uint8_t cathod_no, uint8_t state)
	{
		if( state == HIGH )
		{
			this->_HC595->SetBitNo( -1 * (this->_nCathods - cathod_no) );
		}
		else
		{
			this->_HC595->ClearBitNo( -1 * (this->_nCathods - cathod_no) );
		}
	}


} /* namespace Drivers */
