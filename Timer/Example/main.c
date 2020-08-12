/**
 *  File Name: Main.c
 *  Description: Example on timers, blinking the red led every 1 sec.
 */
#include "GPIO.h"
#include "timer.h"

volatile void myCallBack()
{

    SET_BIT(TIMER5_16,GPTMICR,TATOCINT);        /*Clearing the interrupt bit to receive more interrupts later*/
    TOGGLE_BIT(PORTF,GPIODATA,PIN1);            /*Toggling the red LED*/

}

int main(void)
{
    PIN_CONFIG LED1 = {PORTF,PIN1,OUTPUT,PULL_UP,TWO} ;  /* Internal Red LED*/
    GPIO_configureDigitalPin(&LED1);
    TimerConfigurations TIMER0 = {62500,TIMER5_16,HALF,A,A5,255,PERIODIC,UP};   
                        /*TimerValue,Module,TimerSize,HalfSelect,enableInterrupt,Prescaler,TimerType,CountingType*/
    TIMER_setCallBack(myCallBack);
    TIMER_init(&TIMER0);
    while(1)
    {

    }

}
