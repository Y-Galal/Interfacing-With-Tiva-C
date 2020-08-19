#include "GPIO.h"

volatile uint8 led_select= 1; /* Flag to select the led color */
void delay()        /* Delay function "not an efficient one but works" */
{
    uint32 i =0;
    for(i=0;i<=4000000;i++)
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
    
    while(1)
    {
            if(led_select == 1)
            {
                GPIO_writeData(PORTF, PIN1, HIGH);      /*red*/
                GPIO_writeData(PORTF, PIN2, LOW);
                GPIO_writeData(PORTF, PIN3, LOW);
                led_select++;
            }
            else if (led_select == 2 )
            {
                GPIO_writeData(PORTF, PIN0, LOW);
                GPIO_writeData(PORTF, PIN2, HIGH);      /*green*/
                GPIO_writeData(PORTF, PIN3, LOW);
                led_select++;
            }
            else if (led_select == 3)
            {
                GPIO_writeData(PORTF, PIN0, LOW);
                GPIO_writeData(PORTF, PIN2, LOW);
                GPIO_writeData(PORTF, PIN3, HIGH);      /*blue*/
                led_select=1;                
            }
            delay();
    }
}
