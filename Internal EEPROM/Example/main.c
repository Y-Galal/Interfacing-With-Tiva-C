/**
 *  File Name: main.c
 *  Description: An example to test the internal EEPROM. 
 *              The right switch changes between the color of the led
 *              and the left switch saves the last color to the EEPROM.
 *              if you pressed reset or disconnected the board and connected it again
 *              you will see the saved color in the led.
 */
#include "GPIO.h"
#include "internal_eeprom.h"
#include "interrupts.h"

uint8 colors[8]={0,2,4,6,8,10,12,14};
uint32 offset=0;
void delay()
{
    uint32 i;
    for(i=0;i<800000;i++)
    {
        continue;
    }
}
void callBack()                 /*the function to be called by the ISR */
{
    if(detectPin(PORTF) == PIN0)
    {
        offset= (offset+1)%8;           /*The right switch changes between the colors*/
        clearAfterHandle(PORTF,PIN0);   /*clearing the interrupt*/
    }
    else if(detectPin(PORTF) == PIN4)
    {
        EEPROM_writeData(0,0,offset);   /*the left switch saves the color in block 0 offset 0*/
        clearAfterHandle(PORTF,PIN4);
    }
    clearAfterHandle(PORTF,PIN0);
    clearAfterHandle(PORTF,PIN4);
}

int main(void)
{

    EEPROM_init();                      /*initializing the EEPROM*/
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO};  /*initializing the internal RGB LED*/
    PIN_CONFIG LED2 = {PORTF,PIN2,OUTPUT,PULL_UP,TWO};
    PIN_CONFIG LED3 = {PORTF,PIN3,OUTPUT,PULL_UP,TWO};
    GPIO_configureDigitalPin(&LED1);
    GPIO_configureDigitalPin(&LED2);
    GPIO_configureDigitalPin(&LED3);

    PIN_CONFIG Button1 = {PORTF,PIN0,INPUT,PULL_UP,TWO};  /*configuring the internal switches and enabling interrupt*/
    INTERRUPT S1 = {PORTF,PIN0,EDGE_SENSE,LOW_FALLING};
    GPIO_configureDigitalPin(&Button1);
    GPIO_enableInterrupt(&S1,callBack);

    PIN_CONFIG Button2 = {PORTF,PIN4,INPUT,PULL_UP,TWO};
    INTERRUPT S2 = {PORTF,PIN4,EDGE_SENSE,LOW_FALLING};
    GPIO_configureDigitalPin(&Button2);
    GPIO_enableInterrupt(&S2,callBack);

    EEPROM_readData(0,0,&offset);           /*reading the data saved in block 0 offset 0 to 
                                              light the led with the saved color*/

    while(1)
    {
        ACCESS_REG(PORTF,GPIODATA) = ( ACCESS_REG(PORTF,GPIODATA) & 0xF1  ) | ( colors[offset]  ) ;
                                /*This line writes the LED color to pins 1,2 and 3 to light the LED*/
        delay();                /*delay to see the color*/
    }
	return 0;
}
