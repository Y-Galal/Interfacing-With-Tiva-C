 /******************************************************************************
 *
 * Module: Keypad
 *
 * File Name: keypad.h
 *
 * Description: header file for the keypad
 *
 * Author: Youssef Galal
 *
 *******************************************************************************/


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "GPIO.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
    #define N_col 4

    #define N_row 4

    #define FULL_PORT 0xFF

    #define KEYPAD_PORT_OUT ACCESS_REG(PORTB,GPIODATA)      /*Change these to connect the keypad to another port*/

    #define KEYPAD_PORT_IN PORTB

    #define KEYPAD_PORT_DIR ACCESS_REG(PORTB,GPIODIR)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Keypad_init();
uint8 Keypad_getPressedKey(void);


#endif /* KEYPAD_H_ */
