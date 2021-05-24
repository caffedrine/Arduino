/*
 * Printf.cpp
 *
 *  Created on: Apr 26, 2019
 *      Author: curiosul
 */

#include "Printf.h"

static HardwareSerial *serial;

void printf_init(HardwareSerial *SerialPort, uint32_t BaudRate)
{
	serial = SerialPort;

	// Init serial
	serial->begin(BaudRate);
}

extern int printf(const char *fmt, ...)
{
	int WrittenChars = 0;

	if( !serial )
	{
		return -1;
	}

	va_list argv;
	va_start(argv, fmt);

	for (int i = 0; fmt[i] != '\0'; i++)
	{
		if (fmt[i] == '%')
		{
			// Look for specification of number of decimal places
			int places = 2;
			if (fmt[i + 1] == '.')
				i++; // alw1746: Allows %.4f precision like in stdio printf (%4f will still work).
			if (fmt[i + 1] >= '0' && fmt[i + 1] <= '9')
			{
				places = fmt[i + 1] - '0';
				i++;
			}

			switch (fmt[++i])
			{
			case 'B':
				serial->print("0b"); // Fall through intended
			case 'b':
				serial->print(va_arg(argv, int), BIN);
				break;
			case 'c':
				serial->print((char) va_arg(argv, int));
				break;
			case 'd':
			case 'i':
				serial->print(va_arg(argv, int), DEC);
				break;
			case 'f':
				serial->print(va_arg(argv, double), places);
				break;
			case 'l':
				serial->print(va_arg(argv, long), DEC);
				break;
			case 'o':
				serial->print(va_arg(argv, int) == 0 ? "off" : "on");
				break;
			case 's':
				serial->print(va_arg(argv, const char*));
				break;
			case 'X':
				serial->print("0x"); // Fall through intended
			case 'x':
				serial->print(va_arg(argv, int), HEX);
				break;
			case '%':
				serial->print(fmt[i]);
				break;
			default:
				serial->print("?");
				break;
			}
			WrittenChars++;
		}
		else
		{
			serial->print(fmt[i]);
			WrittenChars++;
		}
	}
	va_end(argv);
	return WrittenChars;
}
