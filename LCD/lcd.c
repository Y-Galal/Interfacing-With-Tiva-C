 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Lcd module
 *
 * Author: Youssef Galal
 *
 *******************************************************************************/

#include "lcd.h"

/* Function Name: delay_1ms
*  Fucntion description:  function taht set a 1ms delay in a 16 mhz clock (not efficient)
*/
void delay_1ms()
{
	uint16 i;
	for(i=0;i<16000;i++)
	{

	}
}

/* Function Name: configPins
*  Fucntion description: Takes the size needed (4bits-8bits) and configures these pins 
*  
*/
static void configPins(uint8 size) 
{
	uint8 i= 0;
	for(i=0;i<8;i++)
	{
	PIN_CONFIG PIN = {PORTB,i,OUTPUT,PULL_UP,TWO};
	GPIO_configureDigitalPin(&PIN);
	}
	for(i=5;i<=7;i++)
	{
		PIN_CONFIG PIN = {PORTC,i,OUTPUT,PULL_UP,TWO};
		GPIO_configureDigitalPin(&PIN);
	}
}

/* Function Name: LCD_init
*  Fucntion description: Initializes the LCD module 
* 
*/
void LCD_init(void)
{
	#if (DATA_BITS_MODE == 4)
		configPins(4);
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
		LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
	#elif (DATA_BITS_MODE == 8)
		configPins(8); /* All pins are output pins  */
		LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
	#endif
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

/* Function Name: LCD_sendCommand
*  Fucntion description: function to send command to the LCD to do something 
*  
*/
void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,RS);
	CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,RW);
	delay_1ms();
	SET_BIT(LCD_CTRL_PORT,GPIODATA,E);
	delay_1ms();
	#if (DATA_BITS_MODE == 4)
		
		ACCESS_REG(LCD_DATA_PORT,GPIODATA) = (ACCESS_REG(LCD_DATA_PORT,GPIODATA) & 0xF0) | ( (command & 0xF0) >> 4);

		delay_1ms();
		CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,E);
		delay_1ms();
		SET_BIT(LCD_CTRL_PORT,GPIODATA,E);

		ACCESS_REG(LCD_DATA_PORT,GPIODATA) = (ACCESS_REG(LCD_DATA_PORT,GPIODATA) & 0xF0) | ( (command & 0x0F) );

		delay_1ms();
		CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,E);
		delay_1ms();

	#elif (DATA_BITS_MODE == 8)
		ACCESS_REG(LCD_DATA_PORT,GPIODATA)  = command;
		delay_1ms();
		CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,E);
		delay_1ms();

	#endif
}

/* Function Name: LCD_displayCharacter
*  Fucntion description: Displays a character on the lcd
*  
*/
void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,GPIODATA,RS); /*RS=1 for data mode*/
	CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,RW); /*RW=0 to write data */
	delay_1ms();
	SET_BIT(LCD_CTRL_PORT,GPIODATA,E);
	delay_1ms();
#if (DATA_BITS_MODE == 4)
	
	ACCESS_REG(LCD_DATA_PORT,GPIODATA) = (ACCESS_REG(LCD_DATA_PORT,GPIODATA) & 0xF0) | ((data & 0xF0) >>4);

	delay_1ms();
	CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,E);
	delay_1ms();
	SET_BIT(LCD_CTRL_PORT,GPIODATA,E);

	
	ACCESS_REG(LCD_DATA_PORT,GPIODATA) = (ACCESS_REG(LCD_DATA_PORT,GPIODATA) & 0xF0) | ( (data & 0x0F)  );
	
	delay_1ms();
	CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,E);
	delay_1ms();
#elif (DATA_BITS_MODE == 8)
	ACCESS_REG(LCD_DATA_PORT,GPIODATA) = data;
	delay_1ms();
	CLEAR_BIT(LCD_CTRL_PORT,GPIODATA,E);
	delay_1ms();
#endif
}

/* Function Name: LCD_displayString
*  Fucntion description: displays a string on the lcd 
*  
*/
void LCD_displayString(const char *Str)
{
	uint8 i=0;
	while(Str[i]!='\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

/* Function Name: LCD_goToRowColumn
*  Fucntion description: shifts the cursor to some place on the lcd
*  
*/
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;
	switch(row)
	{
	case 0 :
		Address = col;
		break;
	case 1 :
		Address = col + 0x40;
		break;
	case 2 :
		Address = col + 0x10;
		break;
	case 3 :
		Address = col + 0x50;
		break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address |SET_CURSOR_LOCATION);
}

/* Function Name: LCD_displayStringRowColumn
*  Fucntion description: shifts the cursor to some place and prints a string on the lcd 
* 
*/
void LCD_displayStringRowColumn(uint8 row,uint8 col, const char *Str)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(Str);
}

/* Function Name: LCD_clearScreen
*  Fucntion description: Clears the screen and goes to the first place 
*  
*/
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}

