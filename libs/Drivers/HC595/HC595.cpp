/*
 * HC595.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: curiosul
 */

#include "HC595.h"

namespace Drivers
{

	HC595::HC595(uint8_t ClockPin, uint8_t DataPin, uint8_t LatchPin, uint8_t RegNo) : _ClockPin(ClockPin, OUTPUT), _DataPin(DataPin, OUTPUT), _LatchPin(LatchPin, OUTPUT), _RegsNo(RegNo)
	{
		this->_Buffer = (uint8_t *)malloc(this->_RegsNo*sizeof(uint8_t));
	}

	HC595::~HC595()
	{
		free(this->_Buffer);
	}


	void HC595::SetAll()
	{
		for(uint8_t i = 0; i < this->_RegsNo; i++)
		{
			this->_Buffer[i] = 0xFF;
		}
	}

	void HC595::ClearAll()
	{
		for(uint8_t i = 0; i < this->_RegsNo; i++)
		{
			this->_Buffer[i] = 0x00;
		}
	}

	void HC595::ToggleAll()

	{
		for(uint8_t i = 0; i < this->_RegsNo; i++)
		{
			this->_Buffer[i] = ~this->_Buffer[i];
		}
	}

	void HC595::WriteRaw(uint8_t *Data, uint8_t len)
	{
		if(len > this->_RegsNo)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] WriteRaw(): Invalid data length: ");
				ERR_PRINTLN(len);
			#endif
			return;
		}

		for(uint8_t i = 0; i < this->_RegsNo; i++)
		{
			this->_Buffer[i] = Data[i];
		}
	}


	void HC595::SetBit(HC595Pin bit, uint8_t RegIndex)
	{
		if(RegIndex >= this->_RegsNo || (uint8_t)bit >= 8)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] SetBit(): Invalid register index: ");
				ERR_PRINTLN(RegIndex);
			#endif
			return;
		}
		this->_Buffer[RegIndex] |= (1 << (uint8_t)bit);
	}

	void HC595::ClearBit(HC595Pin bit, uint8_t RegIndex)
	{
		if(RegIndex >= this->_RegsNo || (uint8_t)bit >= 8)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] ClearBit(): Invalid register index: ");
				ERR_PRINTLN(RegIndex);
			#endif
			return;
		}
		this->_Buffer[RegIndex] &= (~(1 << (uint8_t)bit));
	}

	void HC595::ToggleBit(HC595Pin bit, uint8_t RegIndex)
	{
		if(RegIndex >= this->_RegsNo || (uint8_t)bit >= 8)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] ToggleBit(): Invalid register index: ");
				ERR_PRINTLN(RegIndex);
			#endif
			return;
		}
		this->_Buffer[RegIndex] ^= (1 << (uint8_t)bit);
	}

	void HC595::WriteBit(HC595Pin bit, uint8_t value, uint8_t RegIdx)
	{
		if(RegIdx >= this->_RegsNo || (uint8_t)bit >= 8)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] WriteBit(): Invalid register index: ");
				ERR_PRINTLN(RegIdx);
			#endif
			return;
		}
		if(value == 1)
		{
			this->SetBit(bit, RegIdx);
		}
		else
		{
			this->ClearBit(bit, RegIdx);
		}
	}


	void HC595::WriteByte(uint8_t Byte, uint8_t RegIndex)
	{
		if(RegIndex >= this->_RegsNo)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] WriteByte(): Invalid register index: ");
				ERR_PRINTLN(RegIndex);
			#endif
			return;
		}
		this->_Buffer[RegIndex] = Byte;
	}

	void HC595::ToggleByte(uint8_t RegIdx)
	{
		if(RegIdx >= this->_RegsNo)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] ToggleByte(): Invalid register index: ");
				ERR_PRINTLN(RegIdx);
			#endif
			return;
		}

		this->_Buffer[RegIdx] = ~this->_Buffer[RegIdx];
	}

	void HC595::ClearByte(uint8_t RegIdx)
	{
		if(RegIdx >= this->_RegsNo)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] ClearByte(): Invalid register index: ");
				ERR_PRINTLN(RegIdx);
			#endif
			return;
		}

		this->_Buffer[RegIdx] = 0x00;
	}

	void HC595::SetByte(uint8_t RegIdx)
	{
		if(RegIdx >= this->_RegsNo)
		{
			#if DEBUG == 1
				ERR_PRINT("[ERR][HC595] SetByte(): Invalid register index: ");
				ERR_PRINTLN(RegIdx);
			#endif
			return;
		}

		this->_Buffer[RegIdx] = 0xFF;
	}




} /* namespace Drivers */
