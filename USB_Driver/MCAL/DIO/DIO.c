#include "DIO.h"

void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	/*Add function to check all inputs are valid*/
	uint8 pinNumber = ChannelId&PORT_PIN_MASK;
	uint8 portNumber = (ChannelId&PORT_FIELD_MASK)>>4 ;

	/*Check that pin is initialized first*/
	/*Write level to pin*/
	if(Level==STD_LOW)
	{
		/*Use BSRRH to reset pin*/
		GPIOs[portNumber]->BSRR = (1<<(pinNumber+GPIO_BSRR_BR0_Pos));

	}else if(Level==STD_HIGH)
	{
		/*Use BSRRL to set pin*/
		GPIOs[portNumber]->BSRR = (1<<pinNumber);
	}
	/*Return*/

}

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
	/*Add function to check all inputs are valid*/
	uint8 pinNumber = ChannelId&PORT_PIN_MASK;
	uint8 portNumber = (ChannelId&PORT_FIELD_MASK)>>4 ;

	if((GPIOs[portNumber]->IDR)&(1<<pinNumber))
	{
		return STD_HIGH ;
	}else
	{
		return STD_LOW ;
	}
}


