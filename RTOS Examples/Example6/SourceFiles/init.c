/*
 * init.c
 *
 *  Created on: Sep 3, 2020
 *      Author: youssef
 */
#include "init.h"

extern void UART_callBack();    /*extern for the uart callback function to use it in UART_init*/

void PLL_setClock80()
{
    SysCtlClockSet(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5); /*80 MHz Clock*/
}

void UART_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);    /*Enabling PORTA for UART0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);    /*Enabling UART0*/

    UARTClockSourceSet(UART0_BASE,UART_CLOCK_SYSTEM);   /*UART0 is working using the system clock*/
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),115200,
                        UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
                    /*Setting the UART baudrate, 8 bit mode, one stop bit and no parity bit*/

    UARTEnable(UART0_BASE);                         /*Enabling UART0*/
    UARTIntEnable(UART0_BASE,UART_INT_RT);          /*Enabling Receive timeout interrupt*/
    UARTFIFOEnable(UART0_BASE);                     /*Enabling FIFO*/
    UARTIntRegister(UART0_BASE,UART_callBack);      /*Setting the callback function*/
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1); /*Setting UART0 pins PA0,PA1*/
}

void GPIO_LEDInit()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    /*Enabling PORTF*/

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);    /*Enabling internal red  LEDs*/

}



