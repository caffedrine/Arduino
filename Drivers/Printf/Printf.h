/*
 * Printf.h
 *
 *  Created on: Apr 26, 2019
 *      Author: curiosul
 */

#ifndef PRINTF_H_
#define PRINTF_H_

#include <Arduino.h>

void printf_init(HardwareSerial *SerialPort, uint32_t BaudRate);
int printf(const char* fmt, ...);

#endif /* PRINTF_H_ */
