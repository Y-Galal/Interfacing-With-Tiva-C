/*****************************************************************************
     File Name: usb_handlers.h

     Header file for the usb handlers

*****************************************************************************/
#ifndef USB_HANDLERS_H_
#define USB_HANDLERS_H_

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/usbcdc.h"
#include "usblib/usb-ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdcdc.h"
#include "utils/ustdlib.h"
#include "usb_serial_structs.h"


uint32_t ControlHandler(void *pvCBData, uint32_t ui32Event,uint32_t ui32MsgValue, void *pvMsgData);
uint32_t RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,void *pvMsgData);
uint32_t TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,void *pvMsgData);



#endif /* USB_HANDLERS_H_ */
