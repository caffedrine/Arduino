/*
 * SerialAsync.cpp
 *
 *  Created on: Apr 19, 2019
 *      Author: curiosul
 */

#include "SerialAsync.h"

namespace Drivers
{
	SerialAsync::SerialAsync(HardwareSerial *serialChannel, uint32_t BaudRate)
	{
		this->serial = serialChannel;
		this->serial->begin(BaudRate);
	}

	uint16_t SerialAsync::WriteString(const String &str)
	{
		return this->WriteBytes((uint8_t *)str.c_str(), (uint16_t)str.length());
	}

	uint16_t SerialAsync::WriteBytes(uint8_t *bytes, uint16_t bytes_length)
	{
		// If size if too big then return 0 as not of the bytes will be written
		uint16_t InternalBufferAvailability, SerialBufferAvailability;

        InternalBufferAvailability = this->BufferAvailability();
        SerialBufferAvailability = this->serial->availableForWrite();

		if( bytes_length > (InternalBufferAvailability + SerialBufferAvailability) )
			return 0;


        printf("  -> Internal buffer: %d bytes\n", InternalBufferAvailability);
		printf("  -> Serial buffer  : %d bytes\n", SerialBufferAvailability);
		printf("  -> Total capacity : %d bytes\n", InternalBufferAvailability + SerialBufferAvailability);

		// If size fits in available serial buffer and internal buffer is empty then just send it serial buffer
		if( (InternalBufferAvailability == SERIAL_ASYNC_STATIC_BUFFER_SIZE) && (SerialBufferAvailability >= bytes_length))
		{
			return this->serial->write(bytes, bytes_length);
		}
		else // received data needs to be splitted and send a part to serial and a part is enqueued
		{
			// Send to serial next bytes to be written from buffer
			if( SerialBufferAvailability > 0 )
			{
				// Shift to serial the bytes available internally
				if( InternalBufferAvailability < SERIAL_ASYNC_STATIC_BUFFER_SIZE)
				{
					// Write data from internal buffer to serial
					uint16_t w_len = (((SERIAL_ASYNC_STATIC_BUFFER_SIZE - InternalBufferAvailability) > SerialBufferAvailability) ? (SerialBufferAvailability) : (SERIAL_ASYNC_STATIC_BUFFER_SIZE - InternalBufferAvailability));
					// Loop through all bytes that needs to be send
					for( uint16_t i = 0; i < w_len; i++ )
					{
						this->serial->write(this->BufferPop());
					}

					// Is there still availability after wrote all internal buffer bytes?
					uint16_t remaining_availability_in_serial = SerialBufferAvailability - w_len;
					if( remaining_availability_in_serial > 0 )
					{
						for( uint16_t i = 0; i < remaining_availability_in_serial; i++ )
						{
							this->serial->write( bytes[i] );
						}

						// Remaining bytes in request shall be append to circular buffer
						if( bytes_length > remaining_availability_in_serial )
						{
							this->BufferPush(&bytes[remaining_availability_in_serial], bytes_length - remaining_availability_in_serial);
						}
					}
					else // Serial buffer is full. Append remaining bytes to internal buffer
					{
						this->BufferPush(bytes, bytes_length);
					}
				}
				else
				{
					// Internal buffer is empty. Write as much possible into serial and push the rest into internal buffer
					uint16_t w_len = ((bytes_length > SerialBufferAvailability) ? (SerialBufferAvailability) : (bytes_length));
					for( uint16_t i = 0; i < w_len; i++ )
					{
						this->serial->write(bytes[i]);
					}

					// push remaining bytes to internal buffer
					uint16_t remaining_bytes = bytes_length = w_len;
					for( uint16_t i = 0; i < remaining_bytes; i++ )
					{
						this->BufferPush(&bytes[w_len + i], remaining_bytes);
					}
				}
			}
			else // No space in serial buffer. Write everything in internal static buffer
			{
				this->BufferPush(bytes, bytes_length);
			}
		}

		return bytes_length;
	}

	void SerialAsync::MainFunction()
	{
		// Check whether there are bytes queued to be send
		if( this->BufferAvailability() < SERIAL_ASYNC_STATIC_BUFFER_SIZE)
		{
			uint16_t InternalBufferAvailability, SerialBufferAvailability;
	        InternalBufferAvailability = this->BufferAvailability();
	        SerialBufferAvailability = this->serial->availableForWrite();

			uint16_t write_len = (((SERIAL_ASYNC_STATIC_BUFFER_SIZE - InternalBufferAvailability) > SerialBufferAvailability) ? (SerialBufferAvailability) : (SERIAL_ASYNC_STATIC_BUFFER_SIZE - InternalBufferAvailability));

			printf("Mainfunction write %d bytes", write_len);

			// Loop through all bytes that needs to be send
			for( uint16_t i = 0; i < write_len; i++ )
			{
				this->serial->write(this->BufferPop());
			}
		}
	}

} /* namespace Drivers */
