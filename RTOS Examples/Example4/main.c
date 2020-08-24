/*
    *   This Example uses event groups to blink a led or change the color of the led 
    *  
    *   
*/
#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.h"
#include "pll.h"
#include "queue.h"
#include "event_groups.h"
#include "interrupts.h"


EventGroupHandle_t Flags;   /*creating event group handle*/


void buttonsCallBack()          /*ISR of the two switches that will be called if any switch is pressed*/
{
    if(detectPin(PORTF) == PIN4)
    {
       xEventGroupSetBitsFromISR( Flags,0x01,NULL );    /*setting bit 0 of the event group to do something in task1*/
        clearAfterHandle(PORTF,PIN4);               /*clearing the interrupt*/
    }
    else if(detectPin(PORTF) == PIN0)
    {
        xEventGroupSetBitsFromISR( Flags,0x02,NULL );   /*setting bit 1 of the event group to do something in task1*/
        clearAfterHandle(PORTF,PIN0);                   /*clearing the interrupt*/
    }
    else
    {
        clearAfterHandle(PORTF,PIN0);
        clearAfterHandle(PORTF,PIN4);
    }
    
}

void task1(void *pvParameters)
{
    EventBits_t ReadingBits;        
    uint8 colors[8]={0,2,4,6,8,10,12,14};   /*LED colors*/
    uint8 i=0;
    while(1)
    {
        ReadingBits = xEventGroupWaitBits(Flags,0x03,pdFALSE,pdFALSE,1000); /*this task will be blocked untill we set bit 0 or 1*/
        if(ReadingBits == 0x01)
        {
            i=  (i+1)%8  ;
            ACCESS_REG(PORTF,GPIODATA) = (ACCESS_REG(PORTF,GPIODATA) & 0xF1) | colors[i];   /*changing the color*/

            xEventGroupClearBits(Flags,0x03);       /*clearing bit 0 and 1*/
        }
        else if (ReadingBits == 0x02)
        {
            ACCESS_REG(PORTF,GPIODATA) ^=  ( colors[i] );   /*blinking the led*/

        }
        else if (ReadingBits == 0x03)       
        {
            xEventGroupClearBits(Flags,0x02);
        }
        vTaskDelay(500);        /*delay for 500 ms*/
    }
}


void main()
{
    PLL_setClock(CLK_80);   /*Clock is 80MHz*/
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO};  /*configuring internal leds */
    GPIO_configureDigitalPin(&LED1);
    PIN_CONFIG LED2 = {PORTF,PIN2,OUTPUT,PULL_UP,TWO};
    GPIO_configureDigitalPin(&LED2);
    PIN_CONFIG LED3 = {PORTF,PIN3,OUTPUT,PULL_UP,TWO};
    GPIO_configureDigitalPin(&LED3);

    PIN_CONFIG Button1 = {PORTF,PIN0,INPUT,PULL_UP,TWO};    /* Internal Switch (right switch)*/
    GPIO_configureDigitalPin(&Button1);
    INTERRUPT s1 = {PORTF,PIN0,LEVEL_SENSE,LOW_FALLING};
    GPIO_enableInterrupt(&s1,buttonsCallBack );


    PIN_CONFIG Button2 = {PORTF,PIN4,INPUT,PULL_UP,TWO};    /* Internal Switch (left switch)*/
    INTERRUPT s2 = {PORTF,PIN4,LEVEL_SENSE,LOW_FALLING};

    GPIO_configureDigitalPin(&Button2);
    GPIO_enableInterrupt(&s2,buttonsCallBack);

    Flags = xEventGroupCreate();    /*creating the event group bits (8bits)*/

    TaskHandle_t task1_handle;
    xTaskCreate(task1,"task1",100,NULL,1,&task1_handle);  /*Creating a task*/


    vTaskStartScheduler();  /*Starting RTOS*/
    while(1)
    {

    }
}
