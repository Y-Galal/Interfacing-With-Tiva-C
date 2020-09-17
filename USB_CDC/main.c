/*****************************************************************************
    This is an example that uses USB CDC to communicate with the pc using a
    serial terminal to receive a byte and echo it to the terminal again.
    If the pc sends r,g,b the led color will be red or green or blue. sending any
    other character will turn the led off
*****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "usb_handlers.h"   /*Header file for usb handlers that has everthing*/


void USB_serialInit();

/*A flag to indicate that the usb buffer has data to read it.*/
volatile uint32_t g_ui32Flag = 0;

/*Global flag indicating that a USB configuration has been set*/
volatile bool g_bUSBConfigured = false;


int main(void)
{
    uint8_t dataReceivedFromPC;

    /*80 MHz Clock*/
    SysCtlClockSet(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);
    USB_serialInit();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    /*Enabling PORTF*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);    /*Enabling internal red  LEDs*/

    while(1)
    {
        if(g_ui32Flag == 1)
        {
            USBBufferRead((tUSBBuffer *)&g_sRxBuffer, &dataReceivedFromPC, 1);  /*Reading the value sent from pc*/
            USBBufferWrite((tUSBBuffer *)&g_sTxBuffer,&dataReceivedFromPC, 1);  /*Sending the value again to print it on the terminal*/
            switch(dataReceivedFromPC)
            {
                case 'r':       /*LED will be turned on with red color*/
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,
                                                 (GPIO_PIN_1)|(!GPIO_PIN_2)|(!GPIO_PIN_3));
                    break;
                case 'g':       /*LED will be turned on with green color*/
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,
                                                 (!GPIO_PIN_1)|(!GPIO_PIN_2)|(GPIO_PIN_3));
                    break;
                case 'b':       /*LED will be turned on with blue color*/
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,
                                                 (!GPIO_PIN_1)|(GPIO_PIN_2)|(!GPIO_PIN_3));
                    break;
                default:        /*LED will be turned off*/
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,
                                                 (!GPIO_PIN_1)|(!GPIO_PIN_2)|(!GPIO_PIN_3));
                    break;
            }
            g_ui32Flag=0;   /*clearing the flag */
        }


    }
}



/*
 Function Name: USB_serialInit

 This function is called by to initialize the usb driver as a Communication
 Device Class "CDC"
*/
void USB_serialInit()
{

    /*Configure the required pins for USB operation.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeUSBAnalog(GPIO_PORTD_BASE, GPIO_PIN_5 | GPIO_PIN_4);

    /*Initialize the transmit and receive buffers.*/
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);

    /*Set the USB stack mode to Device mode with VBUS monitoring.*/
    USBStackModeSet(0, eUSBModeForceDevice, 0);

    /*Pass our device information to the USB library and place the device
    on the bus.*/
    USBDCDCInit(0, &g_sCDCDevice);

}
