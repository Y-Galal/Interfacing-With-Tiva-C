
/*
 * Example to print hello world on the LCD
 *
 */
#include "lcd.h"
int main(void)
{
    LCD_init();
    LCD_displayString("Hello World");
    while(1)
    {

    }
	return 0;
}
