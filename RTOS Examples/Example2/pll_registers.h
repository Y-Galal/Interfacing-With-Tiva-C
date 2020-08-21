#ifndef PLL_REGISTERS_H
#define PLL_REGISTERS_H

#define SYSTEM_CONTROL 0x400FE000


#define RCC 0x060

#define ACG 27          /*Auto Clock Gating*/
#define USESYSDIV 22    /*Enable System Clock Divider*/
#define USEPWMDIV 20    /*Enable PWM Clock Divisor*/
 

#define PWRDN 13        /*PLL Power Down*/
#define BYPASS 11       /*PLL Bypass*/

#define MOSCDIS 0       /*Main Oscillator Disable*/

#define RCC2 0x070

#define USERCC2 31      /*Use RCC2*/
#define DIV400 30       /*Divide PLL as 400 MHz versus 200 MHz*/
#define SYSDIV2LSB 22   /*Additional LSB for SYSDIV2*/
#define USBPWRDN 14     /*Power-Down USB PLL*/
#define PWRDN2 13       /*Power-Down PLL 2*/
#define BYPASS2 11      /*PLL Bypass 2*/

#define PWMDIV 0xE0000
#define XTAL_16MHZ 0x540

#endif

