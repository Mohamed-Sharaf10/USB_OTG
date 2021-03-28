/*
 * usb_core.c
 *
 *  Created on: Jan 15, 2021
 *      Author: msharaf
 */
#include "usb_core_device.h"

Std_ReturnType usb_Init()
{
	// Enable Clock gating for OTG_HS

	SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_OTGHSEN);

	// Set the USB turn-around time &  Forced peripheral mode & Select internal USB FS PHY
	MODIFY_REG(USB_OTG_HS->GUSBCFG,USB_OTG_GUSBCFG_TRDT|USB_OTG_GUSBCFG_FDMOD_Msk|USB_OTG_GUSBCFG_PHYSEL_Msk,
			_VAL2FLD(USB_OTG_GUSBCFG_TRDT,0x09)|USB_OTG_GUSBCFG_FDMOD|USB_OTG_GUSBCFG_PHYSEL );

	// Configure the device speed to work with Full speed internal phy
	MODIFY_REG(USB_OTG_HS_DEVICE->DCFG,USB_OTG_DCFG_DSPD_Msk,
			_VAL2FLD(USB_OTG_DCFG_DSPD,0x03));

	//Enable the VBUS sensing
	SET_BIT(USB_OTG_HS->GCCFG,USB_OTG_GCCFG_VBUSASEN);

	// un-mask USB reset , Enumeration done , USB suspend , USB Wakeup , SOF , OTG interrupt ,Mode mismatch interrupt
	SET_BIT(USB_OTG_HS->GINTMSK,USB_OTG_GINTMSK_USBRST|USB_OTG_GINTMSK_ENUMDNEM|USB_OTG_GINTMSK_USBSUSPM
					|USB_OTG_GINTMSK_WUIM|USB_OTG_GINTMSK_OTGINT|USB_OTG_GINTMSK_MMISM|USB_OTG_GINTMSK_OEPINT|
					USB_OTG_GINTMSK_IEPINT);

	// Clear all pending interrupts before enabling the global interrupt

	WRITE_REG(USB_OTG_HS->GINTSTS , 0xFFFFFFFF);

	// Enable Global interrupt mask & set the empty level to zero
	MODIFY_REG(USB_OTG_HS->GAHBCFG,USB_OTG_GAHBCFG_GINT_Msk|USB_OTG_GAHBCFG_TXFELVL_Msk|USB_OTG_GAHBCFG_PTXFELVL_Msk
			,USB_OTG_GAHBCFG_GINT|USB_OTG_GAHBCFG_TXFELVL|USB_OTG_GAHBCFG_PTXFELVL);

	return E_OK ;

}

void usb_softDisconnect()
{
	// Set the soft disconnect bit SDIS inside register USB_HS_DCTL
	SET_BIT(USB_OTG_HS_DEVICE->DCTL ,USB_OTG_DCTL_SDIS );
	// Deactivate the transceiver power
	CLEAR_BIT(USB_OTG_HS->GCCFG,USB_OTG_GCCFG_PWRDWN);
}

void usb_connect()
{
	// Activate the transceiver power
	SET_BIT(USB_OTG_HS->GCCFG,USB_OTG_GCCFG_PWRDWN);
	// Clear the soft disconnect bit SDIS inside register USB_HS_DCTL
	CLEAR_BIT(USB_OTG_HS_DEVICE->DCTL ,USB_OTG_DCTL_SDIS );
}


void usb_gintsts_handler()
{
	volatile uint32_t gintsts = READ_REG(USB_OTG_HS->GINTSTS) ;

	if(gintsts & USB_OTG_GINTSTS_USBRST)
	{
		usb_reset_handler() ;
		//Clear the interrupt
		SET_BIT(USB_OTG_HS->GINTSTS ,USB_OTG_GINTSTS_USBRST );
	}
	else if(gintsts & USB_OTG_GINTSTS_ENUMDNE)
	{
		//Clear the interrupt
		SET_BIT(USB_OTG_HS->GINTSTS ,USB_OTG_GINTSTS_ENUMDNE);
	}else if(gintsts & USB_OTG_GINTSTS_RXFLVL)
	{

	}else if(gintsts & USB_OTG_GINTSTS_IEPINT)
	{

	}else if(gintsts & USB_OTG_GINTSTS_OEPINT)
	{

	}
}

void usb_reset_handler()
{

}

