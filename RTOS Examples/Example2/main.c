/*
    *   This Example takes a value from pc "r,g,b" and lights the led with the selected color
    *   then prints the status of the tasks every 1 second
    *   Hint: Use PuTTy for serial communication
*/
#include "FreeRTOS.h"
#include "task.h"
#include "uart0.h"
#include "GPIO.h"
#include "pll.h"
#include "queue.h"

QueueHandle_t myQueue;  /*Making this queue handle global to be used by two tasks*/
TaskHandle_t UART_handle,LED_handle,Info_handle;    /*Task handles*/

void UART_task(void *pvParameter)   /*Task that gets a character from PC using UART0 and saves it in the queue*/
{
    uint8 dataFromPC=0; /*Value of the character received*/
    myQueue = xQueueCreate( 5, sizeof(uint8) );     /*Creating a queue of 5 characters */
    while(1)
    {
        dataFromPC = UART_receiveByte();        /*receiving the character from PC*/
        
        xQueueSend(myQueue,(void *) &dataFromPC,0); /*Saving the character to the queue*/

        

        vTaskDelay(500);        /*Delay the task for 500 ms*/
    }
}

void LED_task(void *pvParameter)    /*Task that takes the value saved in the queue and 
                                        lights the led with Red or green or blue color*/
{
    uint8 valueFromQueue;
    while(1)
    {
        xQueueReceive(myQueue,(void *)&valueFromQueue,1500);    /*Getting the value from the queue*/
        switch(valueFromQueue)
        {
            case 'r':
                SET_BIT(PORTF,GPIODATA,PIN1);       /*RED LED is on*/
                CLEAR_BIT(PORTF,GPIODATA,PIN2);
                CLEAR_BIT(PORTF,GPIODATA,PIN3);
            break;
            case 'b':
                CLEAR_BIT(PORTF,GPIODATA,PIN1);
                SET_BIT(PORTF,GPIODATA,PIN2);   /*BLUE LED is on*/
                CLEAR_BIT(PORTF,GPIODATA,PIN3);

            break;
            case 'g':
                CLEAR_BIT(PORTF,GPIODATA,PIN1);
                CLEAR_BIT(PORTF,GPIODATA,PIN2);
                SET_BIT(PORTF,GPIODATA,PIN3);       /*GREEN LED is on*/
            break;
        }
        vTaskDelay(500);    /*delay for 500 ms*/
    }  
}

void printInfo(void *pvParameter)   /*Task to print the information about all the tasks in the system*/
{

    uint8 i=0;
    TaskStatus_t *status;
    status = pvPortMalloc(4*sizeof(TaskStatus_t));
    while(1)
    {
        uxTaskGetSystemState(status,4,NULL);
        for(i=0;i<4;i++)
        {
            UART_sendString(status[i].pcTaskName);  /*Printing the name of the tasks*/
            UART_sendNumber(status[i].eCurrentState);   /*Printing the state of the tasks*/
        }
        vTaskDelay(1000);   /*Delay for 1 sec*/
    }
}

void main()
{
    PLL_setClock(CLK_80);   /*Clock is 80MHz*/
    UART_init(80000000 , 115200);   /*UART0 init*/
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO};  /*configuring internal leds */
    GPIO_configureDigitalPin(&LED1);
    PIN_CONFIG LED2 = {PORTF,PIN2,OUTPUT,PULL_UP,TWO};
    GPIO_configureDigitalPin(&LED2);
    PIN_CONFIG LED3 = {PORTF,PIN3,OUTPUT,PULL_UP,TWO};
    GPIO_configureDigitalPin(&LED3);
   
   
    xTaskCreate(UART_task,"UART",100,NULL,2,&UART_handle);  /*Creating the tasks*/
    xTaskCreate(LED_task,"LED",100,NULL,1,&LED_handle);
    xTaskCreate(printInfo,"INFO",100,NULL,3,&Info_handle);

    vTaskStartScheduler();  /*Starting RTOS*/
    while(1)
    {

    }
}
