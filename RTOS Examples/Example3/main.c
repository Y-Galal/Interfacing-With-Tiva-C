/*
    *   This Example is about semaphores and mutexes. we have two tasks that need to use 
    *   one driver (UART0), so we need a mutex to ensure that only one task uses the driver and the
    *   other is waiting for the first task to finish using the driver
    *   Hint: Use PuTTy for serial communication
*/
#include "FreeRTOS.h"
#include "task.h"
#include "uart0.h"
#include "pll.h"
#include "semphr.h"

SemaphoreHandle_t myMutex;          /*Mutex to work with the two tasks*/
uint8 message1[] = "Task1 has the mutex!";
uint8 message2[] = "Task2 has the mutex!";

void task1(void *pvParameters)  /*Task 1 that has the higher priority*/
{
    myMutex = xSemaphoreCreateMutex();  /*creating the mutex*/
    while(1)
    {
        xSemaphoreTake(myMutex,NULL);  /*Taking the mutex*/
        UART_sendString(message1);              /*sending the message and using uart0*/
        xSemaphoreGive(myMutex);                /*giving back the semaphore*/
        vTaskDelay(1000);                       /*delay 1 second to go for the other task*/
    }
}

void task2(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(myMutex,NULL);           /*Taking the mutex*/
        UART_sendString(message2);              /*sending the message and using uart0*/
        xSemaphoreGive(myMutex);                /*giving back the semaphore*/
        vTaskDelay(1000);                       /*delay 1 second */

    }
}



void main()
{
    PLL_setClock(CLK_80);   /*Clock is 80MHz*/
    UART_init(80000000 , 115200);   /*UART0 init*/
   
    TaskHandle_t TaskHandle1,TaskHandle2;

    xTaskCreate(task1,"Task1",100,NULL,2,&TaskHandle1);  /*Creating the tasks*/
    xTaskCreate(task2,"Task2",100,NULL,1,&TaskHandle2);
    

    vTaskStartScheduler();  /*Starting RTOS*/
    while(1)
    {

    }
}
