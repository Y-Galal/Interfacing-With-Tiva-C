/*
 * init.h
 *
 *  Created on: Sep 3, 2020
 *      Author: youssef
 */

#ifndef INIT_H_
#define INIT_H_

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"


void PLL_setClock80();
void UART_init();
void GPIO_LEDInit();



#endif /* INIT_H_ */
