#include "pll.h"



void PLL_setClock(Clock_Select Speed)
{
    uint32 configRCC,configRCC2;

    configRCC = (1<<USESYSDIV) | (PWMDIV) | (XTAL_16MHZ) ;
        /*  
        *   USESYSDIV = 1
        *   BYPASS = 0
        *   XTAL = 10101 "crystal 16 MHz"
        *   MOSCDIS = 0
        *   OSCSRC = 00 to use main oscillator
        */
    configRCC2 = Speed | (1<<DIV400) | (1<<USERCC2) | (1<<USBPWRDN);
        /*
        *   USERCC2 = 1 
        *   DIV400 = 1 
        *   SYSDIV2:SYSDIV2LSB = Required clock speed 
        *   PWRDN2 =0
        *   BYPASS2 =0
        *   OSCSRC2 =0
        *   USBPWRDN = 1
        */

    ACCESS_REG(SYSTEM_CONTROL,RCC) = configRCC;     /*Writing the required configuration to RCC register*/
    ACCESS_REG(SYSTEM_CONTROL,RCC2) = configRCC2;   /*Writing the required configuration to RCC register*/
}
