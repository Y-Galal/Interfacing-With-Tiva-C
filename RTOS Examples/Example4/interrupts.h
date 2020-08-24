#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include "GPIO_registers.h"
#include "macros.h"
#include "std_types.h"
#include "interrupt_registers.h"

#define NULL ((void *)0)

typedef enum
{
    EDGE_SENSE,LEVEL_SENSE,HIGH_RISING,LOW_FALLING,BOTH
}InterruptSense;

typedef struct 
{
    const uint32 Port;
    const uint8 Pin;
    const InterruptSense Sense;
    const InterruptSense Type;
}INTERRUPT;

void PORTAInterruptHandler (void) ;     /*ISR functions what must be added to the startup code*/
                                        /*extern this functions and add them to the vector table to the corresponding place*/
void PORTBInterruptHandler (void) ;

void PORTCInterruptHandler (void);

void PORTDInterruptHandler (void) ;

void PORTEInterruptHandler (void);

void PORTFInterruptHandler (void) ;


void GPIO_enableInterrupt(const INTERRUPT *configInterrupt, volatile void *callbackFunction);

uint8 detectPin(uint32 Port);

void clearAfterHandle(uint32 Port,uint32 Pin);
#endif
