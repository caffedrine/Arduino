/*
 * GpioBase.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: curiosul
 */

#include "GpioBase.h"

namespace Drivers
{
	GpioBase::GpioBase(uint8_t PinNo) :_PinNo(PinNo), _Mode(INPUT)
	{
		Vfb_SetPinMode(this->_PinNo, this->_Mode);
	}

	GpioBase::GpioBase(uint8_t PinNo, uint8_t Mode) : _PinNo(PinNo), _Mode(Mode)
	{
		Vfb_SetPinMode(this->_PinNo, this->_Mode);
	}

	GpioBase::~GpioBase()
	{
	}

	void GpioBase::Set()
	{
			if(this->_Mode == INPUT)
			{
				#if DEBUG == 1
					ERR_PRINT("[ERR][GpioBase] Can't SET a pin set as INPUT: ");
					ERR_PRINTLN(this->_PinNo);
				#endif
				return;
			}

			if(this->_PinNo <= 0 )
			{
				#if DEBUG == 1
					ERR_PRINT("[ERR][GpioBase] Setting invalid pin or not initialized: ");
					ERR_PRINTLN(this->_PinNo);
				#endif
				return;
			}
			Vfb_DigitalWrite(this->_PinNo, HIGH);
	}

	void GpioBase::Clear()
	{
		if(this->_Mode == INPUT)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][GpioBase] Can't SET a pin set as INPUT: ");
				ERR_PRINTLN(this->_PinNo);
			#endif
			return;
		}

		if(this->_PinNo <= 0 )
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][GpioBase] Clearing invalid pin or not initialized: ");
				ERR_PRINTLN(this->_PinNo);
			#endif
			return;
		}
		Vfb_DigitalWrite(this->_PinNo, LOW);
	}

	void GpioBase::Toggle()
	{
		if(this->_Mode == INPUT)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][GpioBase] Can't TOGGLE a pin set as INPUT: ");
				ERR_PRINTLN(this->_PinNo);
			#endif
			return;
		}

		if(this->_PinNo <= 0 )
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][GpioBase] Toggling invalid pin or not initialized: ");
				ERR_PRINTLN(this->_PinNo);
			#endif
			return;
		}
		Vfb_DigitalToggle(this->_PinNo);
	}

	uint8_t GpioBase::Read()
	{
		if(this->_PinNo <= 0 )
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][GpioBase] Invalid pin number or not initialized: ");
				ERR_PRINTLN(this->_PinNo);
			#endif
		}
		return Vfb_DigitalRead(this->_PinNo);
	}

} /* namespace Drivers */
