/*****************************************************************************
     File Name: usb_handlers.c

     source file for the usb handlers (Control - TX - RX)

*****************************************************************************/

#include "usb_handlers.h"

/*Global flag indicating that a USB configuration has been set.*/
extern volatile bool g_bUSBConfigured;

extern volatile uint32_t g_ui32Flag;   /*A flag to indicate that the usb buffer has data to read it.*/


/*
 * Function Name: USB_setLineCoding
 *
 * This function is called by the control handler when the get line event is passed to it
 * to set the serial communication port between the host (PC) and the device (Tiva board)
 */

static void USB_setLineCoding(tLineCoding *psLineCoding)
{

    psLineCoding->ui32Rate = 115200; /*Setting the baudrate*/

    psLineCoding->ui8Databits = 8; /*data length is 8*/

    psLineCoding->ui8Parity = USB_CDC_PARITY_NONE; /*No Parity*/

    psLineCoding->ui8Stop = USB_CDC_STOP_BITS_1;    /* 1 stop bit*/
}

/*****************************************************************************

 Function Name: ControlHandler

 Handles CDC driver notifications related to control and setup of the device.

 \param pvCBData is the client-supplied callback pointer for this channel.
 \param ui32Event identifies the event we are being notified about.
 \param ui32MsgValue is an event-specific value.
 \param pvMsgData is an event-specific pointer.

 This function is called by the CDC driver to perform control-related
 operations on behalf of the USB host.  These functions include setting
 and querying the serial communication parameters, setting handshake line
 states and sending break conditions.

 \return The return value is event-specific.

*****************************************************************************/
uint32_t ControlHandler(void *pvCBData, uint32_t ui32Event,
               uint32_t ui32MsgValue, void *pvMsgData)
{
    /* Which event are we being asked to process?*/
    switch(ui32Event)
    {
        /* We are connected to a host and communication is now possible.*/
        case USB_EVENT_CONNECTED:
            g_bUSBConfigured = true;
            USBBufferFlush(&g_sTxBuffer);   /* Flush our buffers.*/
            USBBufferFlush(&g_sRxBuffer);
            break;

        case USB_EVENT_DISCONNECTED: /*The host has disconnected.*/
            g_bUSBConfigured = false;
            break;

        case USBD_CDC_EVENT_GET_LINE_CODING: /* Return the current serial communication parameters.*/
            USB_setLineCoding(pvMsgData);
            break;

        default:
            break;
    }
    return 0;
}

/*****************************************************************************
 Function Name: TxHandler

 Handles CDC driver notifications related to the transmit channel (data to
 the USB host).

 \param ui32CBData is the client-supplied callback pointer for this channel.
 \param ui32Event identifies the event we are being notified about.
 \param ui32MsgValue is an event-specific value.
 \param pvMsgData is an event-specific pointer.

 This function is called by the CDC driver to notify us of any events
 related to operation of the transmit data channel (the IN channel carrying
 data to the USB host).
 We don't need this function in this specific application.

*****************************************************************************/
uint32_t TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,void *pvMsgData)
{

    switch(ui32Event)
    {
        case USB_EVENT_TX_COMPLETE:

            /* Since we are using the USBBuffer, we don't need to do anything
             here. */

            break;


        default:
            break;


    }
    return 0;
}

/*****************************************************************************

 Function Name: RxHandler
 Handles CDC driver notifications related to the receive channel (data from
 the USB host).

 \param ui32CBData is the client-supplied callback data value for this channel.
 \param ui32Event identifies the event we are being notified about.
 \param ui32MsgValue is an event-specific value.
 \param pvMsgData is an event-specific pointer.

 This function is called by the CDC driver to notify us of any events
 related to operation of the receive data channel (the OUT channel carrying
 data from the USB host).

 !NOTE: In this handler we only need the receive event. you can add more events in this
          function.

 \return The return value is event-specific.

*****************************************************************************/
uint32_t RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,void *pvMsgData)
{


    if(ui32Event == USB_EVENT_RX_AVAILABLE) /*Incoming data event*/
    {

       g_ui32Flag=1;

    }

    return 0;
}



