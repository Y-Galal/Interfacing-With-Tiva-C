#ifndef LCD_H_
#define LCD_H_


#include "GPIO.h"

#define DATA_BITS_MODE 4
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* Hw Pins */
#define RS PIN5
#define RW PIN6
#define E PIN7

#define LCD_CTRL_PORT PORTC

#define LCD_DATA_PORT PORTB


/* LCD Commands */
#define CLEAR_COMMAND 0x01                      
#define FOUR_BITS_DATA_MODE 0x20                    
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28         
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38        
#define CURSOR_ON 0x0E                          
#define CURSOR_OFF 0x0C                         
#define SET_CURSOR_LOCATION 0x80





/********************************************************
 *                   Function prototypes                *
 ********************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col, const char *Str);
void LCD_clearScreen(void);



void delay_1ms();



#endif
