/*
*   File name: GPIO.h
*   Created By: Youssef Galal
*   Description: header file for Interfacing with I/O ports with different modes in Tiva C board
*   Created On: 19-7-2020
*/

#ifndef GPIO_H
#define GPIO_H

#include "std_types.h"
#include "macros.h"
#include "GPIO_registers.h"

/* ************************************ */
/*          Configurations              */
/* ************************************ */
typedef enum
{
    INPUT,OUTPUT
}TypeOfPin;

typedef enum
{
    PULL_UP,PULL_DOWN,OPEN_DRAIN
}DriveType;

typedef enum
{
    TWO,FOUR,EIGHT
}Strength;

typedef enum
{
    LOW,
    HIGH
}DigitalOutput;

typedef struct
{
    const uint32 Port;      /* Required Port */
    const uint32 Pin;       /* Required Pin */
    const uint8 Type;       /* input or output */
    const uint8 Drive;      /* pull up or down or open drain*/
    const uint8 Current;    /* current strength in the pin*/
}PIN_CONFIG;


/* ************************************ */
/*          Public Functions            */
/* ************************************ */
void GPIO_configureDigitalPin(const PIN_CONFIG *config);

void GPIO_writeData(uint32 Port, uint32 Pin,uint8 data);

uint8 GPIO_readData(uint32 Port, uint32 Pin);



#endif





