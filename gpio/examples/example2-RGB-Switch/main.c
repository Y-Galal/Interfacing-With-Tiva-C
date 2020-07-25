#include "GPIO.h"

volatile uint8 led_select= 1;   /* Flag to select the led color */
volatile uint8 status=0;        /* Flag to check the status of the switch*/
void delay()                    /* Delay function "not an efficient one but works" */
{
    uint32 i =0;
    for(i=0;i<=180000;i++)
    {
        continue;
    }
}
int main()
{
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO} ;  /* Internal Red LED*/
    PIN_CONFIG LED2 = {PORTF,PIN2,OUTPUT,PULL_UP,TWO} ;  /* Internal Green LED*/
    PIN_CONFIG LED3 = {PORTF,PIN3,OUTPUT,PULL_UP,TWO} ;  /* Internal Blue LED*/
    GPIO_configureDigitalPin(&LED1);                        /* Sending the configuration structure to set the required pin*/
    GPIO_configureDigitalPin(&LED2);
    GPIO_configureDigitalPin(&LED3);
    
    PIN_CONFIG Button1 = {PORTF,PIN0,INPUT,PULL_UP,TWO};    /* Internal Switch (right switch)*/
    GPIO_configureDigitalPin(&Button1);

    while(1)
    {
            status = GPIO_readData(PORTF, PIN0);            /* reading the switch value */
            if(!status)                                     /* the switch is pull up by default so it becomes 0 when it's pressed */
            {
                if(led_select == 1)                         
                {
                    GPIO_writeData(PORTF, PIN1, HIGH);              /* red */
                    GPIO_writeData(PORTF, PIN2, LOW);
                    GPIO_writeData(PORTF, PIN3, LOW);
                    led_select++;
                }
                else if (led_select == 2 )                      /* green */
                {
                    GPIO_writeData(PORTF, PIN1, LOW);
                    GPIO_writeData(PORTF, PIN3, HIGH);
                    GPIO_writeData(PORTF, PIN2, LOW);
                    led_select++;
                }
                else if (led_select == 3)                       /* blue */
                {
                    GPIO_writeData(PORTF, PIN1, LOW);
                    GPIO_writeData(PORTF, PIN3, LOW);
                    GPIO_writeData(PORTF, PIN2, HIGH);
                    led_select=1;
                }
            }
            delay();                                        /* delay */
    }
}
