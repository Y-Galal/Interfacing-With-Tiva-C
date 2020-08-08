/*
*   File name: uart0.h
*   Created By: Youssef Galal
*   Description: header file for uart0 to communicate with pc
*   Created On: 5-8-2020
*/




#ifndef UART_H
#define UART_H

#include "std_types.h"
#include "macros.h"
#include "uart_registers.h"
#include "GPIO_registers.h"







void UART_init(uint32 clock , uint32 baudrate);

void UART_sendByte(const uint8 data);

uint8 UART_receiveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #


#endif
