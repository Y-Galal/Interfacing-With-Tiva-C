#ifndef TIMER_H
#define TIMER_H

#include "timer_registers.h"
#include "macros.h"
#include "std_types.h"
#include "interrupt_registers.h"

#define NULL ((void *)(0))

/********   Important Definitions **********/
typedef enum
{
    FULL,HALF=0x4
}TimerSize;

typedef enum
{
    ONE_SHOT=1,PERIODIC=2
}TimerType;

typedef enum
{
    DOWN=0,UP=16
}CountDir;

typedef enum
{
    A,B,A0=19,B0=20,A1=21,B1=22,A2=23,B2=24,A3=35,B3=36,A4=70,B4=71,A5=92,B5=93,AW0=94,BW0=95,AW1=96,
    BW1=97,AW2=98,BW2=99,AW3=100,BW3=101,AW4=102,BW4=103,AW5=104,BW5=105
}HalfSelect;


typedef struct 
{
    uint64 TimerValue;
    uint32 Module;
    TimerSize Size;
    HalfSelect Half;
    HalfSelect TimerSelect;
    uint8 Prescale;
    TimerType Type;
    CountDir Direction;

}TimerConfigurations;

/****************   Public functions    ***********/

void TIMER_init(const TimerConfigurations *config);

void TIMER_setCallBack( volatile void (*timerCallBack)() );

void TIMER_deinit(uint32 Module);

void TIMER_ISR();
#endif

