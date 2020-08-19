/*
*   Description: Main file for FREERTOS example 1, Blinking two leds with different periods
*   Date: 19-8-2020
*/
#include "pll.h"
#include "GPIO.h"
#include "FREERTOS.h"
#include "task.h"

void blink1 (void *pvParameters)    /*Task 1 code to blink the Red LED every 1 sec*/
{
    TickType_t xLastWakeTime = xTaskGetTickCount();           /*getting the current tick count */
    const TickType_t xFrequency = 1000;     /*Period is 1000ms*/

    while(1)
    {
        TOGGLE_BIT(PORTF,GPIODATA,PIN1);    /*Toggling the led*/

        vTaskDelayUntil(&xLastWakeTime,xFrequency); /*Delay for 1000ms*/


    }
}
void blink2 (void *pvParameters)    /*Task 1 code to blink the blue LED every 5 sec*/
{
    TickType_t xLastWakeTime= xTaskGetTickCount();
    const TickType_t xFrequency = 5000; /*Period is 6000ms*/
    while(1)
    {
        TOGGLE_BIT(PORTF,GPIODATA,PIN2);             /*Toggling the led*/
        vTaskDelayUntil(&xLastWakeTime,xFrequency);     /*Delay for 5000ms*/

    }
}

int main(void)
{
    PLL_setClock(CLK_80);       /*Setting the clock to be 80 MHz*/
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO};  /*configuring internal leds */
    GPIO_configureDigitalPin(&LED1);
    PIN_CONFIG LED2 = {PORTF,PIN2,OUTPUT,PULL_UP,TWO};
    GPIO_configureDigitalPin(&LED2);
    TaskHandle_t first_task,second_task;
    xTaskCreate(blink1,"LED1",100,NULL,2,&first_task);  /*Creating Task1*/
    xTaskCreate(blink2,"LED2",100,NULL,1,&second_task); /*creating task2 */
    vTaskStartScheduler();                              /*Starting FREERTOS */
    while(1)
    {

    }
	return 0;
}
