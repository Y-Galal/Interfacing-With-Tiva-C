

#ifndef GPIO_REGISTERS
#define GPIO_REGISTERS

/* Defining GPIO Registers' offset, See the datasheet page 660 */
/*****************************************************************************/
#define GPIODATA 0x3FC  /* GPIO Data "DATA SHEET IS WRONG"*/

#define GPIODIR 0x400  /* GPIO Direction*/ 
/* (0 is input (default) and 1 is output)*/

#define GPIOIS 0x404  /* GPIO Interrupt Sense*/   
/* 1 for levels (High or Low) and 0 for edges (+ve or -ve) */

#define GPIOIBE 0x408  /* GPIO Interrupt Both Edges*/ 
/*  1 -> Both edges on the corresponding pin trigger an interrupt regardless
 *   of the corresponding bit in the (GPIOIEV) register
*  0 "default" -> GPIOEV controls everything */

#define GPIOIEV 0x40C  /* GPIO Interrupt Event*/
/*  0 -> A falling edge or a Low level on the corresponding pin triggers
 *  an interrupt.
 *  1 -> A rising edge or a High level on the corresponding pin triggers
 *  an interrupt. 
*/


#define GPIOIM 0x410  /* GPIO Interrupt Mask*/
/*
 *  0 -> The interrupt from the corresponding pin is masked.
 *  1 -> The interrupt from the corresponding pin is sent to the interrupt controller.
*/

#define GPIORIS 0x414  /* GPIO Raw Interrupt Status*/
/*
*    0 -> An interrupt condition has not occurred on the corresponding
*    pin.

*    1 -> An interrupt condition has occurred on the corresponding pin.
    
*    For edge-detect interrupts, this bit is cleared by writing a 1 to the
*    corresponding bit in the GPIOICR register.

*    For a GPIO level-detect interrupt, the bit is cleared when the level is
*    deasserted.
*/

#define GPIOMIS 0x418  /* GPIO Masked Interrupt Status*/
/* same as above but for Masked interrupts*/

#define GPIOICR 0x41C  /* GPIO Interrupt Clear*/
/*
*    0 -> The corresponding interrupt is unaffected.
*    1 -> The corresponding interrupt is cleared.
    
*    if the interrupt is level-detect setting or resetting a bit here has no effect.
*/

#define GPIOAFSEL 0x420  /* GPIO Alternate Function Select*/
/*
*    0 -> The associated pin functions as a GPIO and is controlled by the GPIO registers.

*    1 -> The associated pin functions as a peripheral signal and is controlled by
*    the alternate hardware function.
*/

#define GPIODR2R 0x500  /* GPIO 2-mA Drive Select*/
/*
*    0 -> The drive for the corresponding GPIO pin is controlled by the
*    GPIODR4R or GPIODR8R register.

*    1 -> The corresponding GPIO pin has 2-mA drive.
*/

#define GPIODR4R 0x504  /* GPIO 4-mA Drive Select*/
/*
*    0 -> The drive for the corresponding GPIO pin is controlled by the
*    GPIODR2R or GPIODR8R register.

*    1 -> The corresponding GPIO pin has 4-mA drive.
*/

#define GPIODR8R 0x508  /* GPIO 8-mA Drive Select*/
/*
*    0 ->The drive for the corresponding GPIO pin is controlled by the
*    GPIODR2R or GPIODR4R register.

*    1 -> The corresponding GPIO pin has 8-mA drive.
*/

#define GPIOODR 0x50C  /* GPIO Open Drain Select*/
/*
*    0 -> The corresponding pin is not configured as open drain.
*    1 -> The corresponding pin is configured as open drain.
*/

#define GPIOPUR 0x510  /* GPIO Pull-Up Select*/
/* 
*    0 -> The corresponding pin's weak pull-up resistor is disabled.
*    1 -> The corresponding pin's weak pull-up resistor is enabled.
*    Setting a bit in the GPIOPDR register clears the corresponding bit in
*    the GPIOPUR register.
*/
#define GPIOPDR 0x514  /* GPIO Pull-Down Select*/
/* Same as GPIOPUR*/

#define GPIOSLR 0x518  /* GPIO Slew Rate Control Select*/
/*
*    0 -> Slew rate control is disabled for the corresponding pin.
*    1 -> Slew rate control is enabled for the corresponding pin.
*/

#define GPIODEN 0x51C  /* GPIO Digital Enable*/
/*
*    0 -> The digital functions for the corresponding pin are disabled.
*    1 -> The digital functions for the corresponding pin are enabled.
*/

#define GPIOLOCK 0x520  /* GPIO Lock*/
/*
*    0x1 -> The GPIOCR register is locked and may not be modified.
*    0x0 -> The GPIOCR register is unlocked and may be modified.
*    if you write UNLOCK_REG to the register it will unlock the GPIOCR
*   any other value will lock it again
*/
#define GPIOCR 0x524  /* GPIO Commit*/
/*
*    0 -> The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or
*    GPIODEN bits cannot be written.
*    1 -> The corresponding GPIOAFSEL, GPIOPUR, GPIOPDR, or
*    GPIODEN bits can be written.
*/

#define GPIOAMSEL 0x528  /* GPIO Analog Mode Select*/
/*
*    0 -> The analog function of the pin is disabled, the isolation is
*    enabled, and the pin is capable of digital functions as specified
*   by the other GPIO configuration registers.

*    1 -> The analog function of the pin is enabled, the isolation is
*    disabled, and the pin is capable of analog functions.
*/

#define GPIOPCTL 0x52C  /* GPIO Port Control*/


#define GPIOADCCTL 0x530  /* GPIO ADC Control*/
/*
*    0 -> The corresponding pin is not used to trigger the ADC.
*    1 -> The corresponding pin is used to trigger the ADC.
*/

#define GPIODMACTL           0x534  /* GPIO DMA Control*/
/*
*    0 -> The corresponding pin is not used to trigger the μDMA.
*    1 -> The corresponding pin is used to trigger the μDMA.
*/

#define GPIOSI               0x00000538  /* GPIO Select Interrupt*/
#define GPIODR12R            0x0000053C  /* GPIO 12-mA Drive Select*/
#define GPIOWAKEPEN          0x00000540  /* GPIO Wake Pin Enable*/
#define GPIOWAKELVL          0x00000544  /* GPIO Wake Level*/
#define GPIOWAKESTAT         0x00000548  /* GPIO Wake Status*/
#define GPIOPP               0x00000FC0  /* GPIO Peripheral Property*/
#define GPIOPC               0x00000FC4  /* GPIO Peripheral Configuration*/
/*****************************************************************************/

#define SYSTEM_CONTROL          0x400FE000 /* System control register base address */
#define RCGCGPIO                0x00000608 /* GPIO Run Mode Clock Gating Control register offset */
                                            /* To enable clock for a port we should set the corresponding bit in this register*/
                                            /* These bits are in bits[5:0] in this register*/

#define UNLOCK_REG 0x4C4F434B /* Value to  be put ion GPIOLOCK Register to unlock */ 
#define LOCK_REG 0x00000022


#define BIT0 0
#define BIT1 1
#define BIT2 2
#define BIT3 3
#define BIT4 4
#define BIT5 5
#define BIT6 6
#define BIT7 7
#define BIT8 8
#define BIT9 9
#define BIT10 10
#define BIT11 11
#define BIT12 12
#define BIT13 13
#define BIT14 14
#define BIT15 15
#define BIT16 16
#define BIT17 17
#define BIT18 18
#define BIT19 19
#define BIT20 20
#define BIT21 21
#define BIT22 22
#define BIT23 23
#define BIT24 24
#define BIT25 25
#define BIT26 26
#define BIT27 27
#define BIT28 28
#define BIT29 29
#define BIT30 30
#define BIT31 31

#endif
