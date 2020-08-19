/*
*important macros for any peripheral
*/

#ifndef MACROS_H
#define MACROS_H

/*********** Important Macros *************/

/* Access a Register using the base and the offset*/
/* we cast the address (base + Offset) to a volatile unsigned long pointer and dereferencing it with the * operator */
#define ACCESS_REG(BASE,OFFSET) ( * ( (volatile unsigned long * )(BASE+OFFSET) ) )

/* Set a certain bit in any register */

#define SET_BIT(BASE,OFFSET,BIT) ( ACCESS_REG(BASE,OFFSET) |=(1<<BIT))

/* Clear a certain bit in any register */

#define CLEAR_BIT(BASE,OFFSET,BIT) ( ACCESS_REG(BASE,OFFSET) &=(~(1<<BIT)))

/* Toggle a certain bit in any register */

#define TOGGLE_BIT(BASE,OFFSET,BIT) ( ACCESS_REG(BASE,OFFSET)^=(1<<BIT))

/* Check if a specific bit is set in any register and return true if yes */

#define BIT_IS_SET(BASE,OFFSET,BIT) ( ACCESS_REG(BASE,OFFSET) & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */

#define BIT_IS_CLEAR(BASE,OFFSET,BIT)  ( ! (ACCESS_REG(BASE,OFFSET) & (1<<BIT)) )
/********************************************************************************/










/*********** GPIO Ports and Pins (Advanced Peripheral Bus Only) ***************/
#define PORTA 0x40004000
#define PORTB 0x40005000
#define PORTC 0x40006000
#define PORTD 0x40007000
#define PORTE 0x40024000
#define PORTF 0x40025000

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7 
/********************************************************************************/



#endif
