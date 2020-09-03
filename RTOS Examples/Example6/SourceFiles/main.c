/******************************************************************
 *  FreeRTOS & TivaWare Example
 *  Description: This example uses software timers to toggle a led with different speeds
 *              it uses UART0 to pc to change the frequency of the timer to change toggling frequency
 *              Inputs        Output
 *              a       -->   increase in led frequency
 *              s       -->   decreasing in led frequency
 *              d       -->   stops the timer (stops toggling)
 *              f       -->   starts the timer again with default frequency (1000 ticks)
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
#include "timers.h"
#include "init.h"       /*header file that have init functions for (UART0,Red LED, PLL)*/

uint8_t g_dataFromUART;        /*Variable to handle the data received from PC*/
SemaphoreHandle_t g_readKeyPermission;  /*Semaphore handle*/
TimerHandle_t g_toggleLEDTimer;         /*software timer handle*/

void UART_callBack()        /*UART0 ISR*/
{
        g_dataFromUART = UARTCharGet(UART0_BASE);    /*getting the data from UART0*/
        UARTCharPut (UART0_BASE, g_dataFromUART);     /*Showing the character in PuTTY Terminal*/
        xSemaphoreGiveFromISR(g_readKeyPermission,NULL);    /*giving a semaphore to the task to read the value*/
        UARTIntClear(UART0_BASE,UART_INT_RT);       /*Clearing the interrupt*/
}

void TimerCallBack(TimerHandle_t myTimer)       /*Timer Callback function*/
{
    static uint8_t status=0;

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,status);    /*writing the value on PortF pin1*/
    status ^= 0x2;                                  /*Toggling the value to toggle the led*/
}

void vLEDControl(void *pvParameters)
{
    TickType_t timerPeriod=1000;        /*Default value of the period of the timer*/
    while(1)
    {
        if(xSemaphoreTake( g_readKeyPermission, pdMS_TO_TICKS(1000) ) == pdTRUE)   /*Taking the semaphore*/
                {
                    switch(g_dataFromUART)
                    {
                        case 'a':
                            timerPeriod = (timerPeriod==0)? 10 : timerPeriod / 2;   /*To avoid having 0 period*/
                            xTimerChangePeriod( g_toggleLEDTimer,timerPeriod,0);
                            break;
                        case 's':
                            timerPeriod *= 2;                                       /*decreasing the frequency*/
                            xTimerChangePeriod( g_toggleLEDTimer,timerPeriod,0);
                            break;
                        case 'd':
                            xTimerStop( g_toggleLEDTimer , 0 );                 /*Stopping the timer*/
                            break;
                        case 'f':
                            xTimerChangePeriod( g_toggleLEDTimer,1000,0);      /*Writing default period of the timer*/
                            xTimerReset(g_toggleLEDTimer,0);                    /*Starting the timer again*/
                            break;
                        default:
                            break;
                    }
                }
    }
}


void main(void)
{
    TaskHandle_t LEDControl_Handle;       /*A handle for task1*/

    /*      Initializing PLL, UART0, Red LED        */
    PLL_setClock80();           /*Setting the clock to 80 MHz*/
    UART_init();                /*initializing UART0*/
    GPIO_LEDInit();             /*Initializing red LED*/

    xTaskCreate(vLEDControl,"LED Control",100,NULL,1,&LEDControl_Handle);     /*Creating the task*/
    g_readKeyPermission = xSemaphoreCreateBinary();         /*Creating a binary Semaphore*/

    g_toggleLEDTimer = xTimerCreate( "LED Toggle",   1000, pdTRUE, (void *) 0,TimerCallBack);   /*Creating the software timer*/
    xTimerStart( g_toggleLEDTimer, 0 );         /*Starting the timer*/


    vTaskStartScheduler();                                  /*Starting the system*/
    while(1)
    {

    }

}
