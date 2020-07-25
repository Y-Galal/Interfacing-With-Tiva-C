
#include "GPIO.h"
#include "interrupts.h"
uint8 flag_button1=0;       /*Flag for detecting switch 1*/
uint8 flag_button2=0;       /*Flag for detecting switch 2 */

void delay()                /*delay function, not an efficient way*/
{
    uint32 i =0;
    for(i=0;i<=360000;i++)
    {
        continue;
    }
}

void callBack()                 /*the function to be called by the ISR */
{
    if(detectPin(PORTF) == PIN0)
    {
        flag_button1=1;
        flag_button2=0;
        clearAfterHandle(PORTF,PIN0);
    }
    else if(detectPin(PORTF) == PIN4)
    {
        flag_button1=0;
        flag_button2=1;
        clearAfterHandle(PORTF,PIN4);
    }
    
    clearAfterHandle(PORTF,PIN0);
    clearAfterHandle(PORTF,PIN4);
}

int main(void)
{
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO};          /*configuring the rgb leds*/
    PIN_CONFIG LED2 = {PORTF,PIN2,OUTPUT,PULL_UP,TWO};
    PIN_CONFIG LED3 = {PORTF,PIN3,OUTPUT,PULL_UP,TWO};

    GPIO_configureDigitalPin(&LED1);
    GPIO_configureDigitalPin(&LED2);
    GPIO_configureDigitalPin(&LED3);

    PIN_CONFIG Button1 = {PORTF,PIN0,INPUT,PULL_UP,TWO};            /*configuring the switch and enabling interrupt*/
    INTERRUPT S1 = {PORTF,PIN0,EDGE_SENSE,LOW_FALLING};
    GPIO_configureDigitalPin(&Button1);
    GPIO_enableInterrupt(&S1,callBack);
    
    PIN_CONFIG Button2 = {PORTF,PIN4,INPUT,PULL_UP,TWO};
    INTERRUPT S2 = {PORTF,PIN4,EDGE_SENSE,LOW_FALLING};
    GPIO_configureDigitalPin(&Button2);
    GPIO_enableInterrupt(&S2,callBack);
    


    while(1)
    {
        if(flag_button1 == 1 )                      /*if Switch 1 is pressed the led will blink*/
        {
            GPIO_writeData(PORTF,PIN1,HIGH);
            GPIO_writeData(PORTF,PIN2,LOW);
            GPIO_writeData(PORTF,PIN3,LOW);
            delay();
            GPIO_writeData(PORTF,PIN1,HIGH);
            GPIO_writeData(PORTF,PIN2,HIGH);
            GPIO_writeData(PORTF,PIN3,LOW);
            delay();
            GPIO_writeData(PORTF,PIN1,LOW);
            GPIO_writeData(PORTF,PIN2,HIGH);
            GPIO_writeData(PORTF,PIN3,HIGH);
            delay();
            GPIO_writeData(PORTF,PIN1,HIGH);
            GPIO_writeData(PORTF,PIN2,LOW);
            GPIO_writeData(PORTF,PIN3,HIGH);
            delay();
            GPIO_writeData(PORTF,PIN1,HIGH);
            GPIO_writeData(PORTF,PIN2,LOW);
            GPIO_writeData(PORTF,PIN3,LOW);
            delay();
        }
        if(flag_button2 == 1)                       /*if the second switch is pressed, you will see white light */
        {
            GPIO_writeData(PORTF,PIN1,HIGH);
            GPIO_writeData(PORTF,PIN2,HIGH);
            GPIO_writeData(PORTF,PIN3,HIGH);
            delay();
        }
        
    }
	return 0;
}
