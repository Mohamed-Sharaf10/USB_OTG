/*
 * usb_core.h
 *
 *  Created on: Jan 15, 2021
 *      Author: msharaf
 */

#ifndef USB_USB_CORE_DEVICE_H_
#define USB_USB_CORE_DEVICE_H_
#include "std.h"

#define USB_OTG_HS_DEVICE  ((USB_OTG_DeviceTypeDef *)(USB_OTG_HS_PERIPH_BASE + 0x800))

Std_ReturnType usb_Init();

void usb_softDisconnect();

void usb_connect() ;

/*
 * !Description : Handler for the USB reset bus
 * */
void usb_reset_handler();

/*
 * !Description : Function will poll on the interrupt status for the USB_OTG
 * */

void usb_gintsts_handler();
#endif /* USB_USB_CORE_DEVICE_H_ */
