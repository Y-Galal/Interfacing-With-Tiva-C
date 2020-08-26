/******************************************************************
 *  FreeRTOS & TivaWare Example
 *  Description: This example takes an input from pc then lights the led with different colors
 *       If the input was 'x' the color will change. If it's not 'x' the led will be turned off
 *  Note: This example uses TivaWare API(UART0,GPIO) and FreeRTOS (Semaphores,Task scheduler)
 *
 ******************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


uint32_t g_dataFromUART;        /*Variable to handle the data received from PC*/
SemaphoreHandle_t colorGivePermission;  /*Semaphore handle*/

void UART_callBack()        /*UART0 ISR*/
{
        g_dataFromUART = UARTCharGet(UART0_BASE);    /*getting the data from UART0*/
        xSemaphoreGiveFromISR(colorGivePermission,NULL);
        UARTIntClear(UART0_BASE,UART_INT_RT);       /*Clearing the interrupt*/
}


void task1(void *pvParameters)
{
    uint8_t colors[7]={2,4,6,8,10,12,14};   /*LED colors*/
    uint8_t i=0;
    while(1)
    {

        if(xSemaphoreTake(colorGivePermission,( TickType_t ) 1000) == pdTRUE)   /*Taking the semaphore*/
        {

            if(g_dataFromUART == 'x')
            {
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,colors[i]);
                i= (i+1)%7;
            }
            else
            {
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
            }
        }
    }
}


void main(void)
{
    TaskHandle_t TaskHandle1;       /*A handle for task1*/

    SysCtlClockSet(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5); /*80 MHz Clock*/

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    /*Enabling PORTF*/

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);    /*Enabling internal LEDs*/

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


    xTaskCreate(task1,"Task1",100,NULL,1,&TaskHandle1);     /*Creating the task*/
    colorGivePermission = xSemaphoreCreateBinary();         /*Creating a binary Semaphore*/

    vTaskStartScheduler();                                  /*Starting the system*/
    while(1)
    {

    }

}
