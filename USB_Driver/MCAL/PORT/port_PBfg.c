#include "port.h"

#define PORT_PORTG_PIN_SIZE			(0x02U)
#define PORT_PORTA_PIN_SIZE			(0x01U)
#define PORT_PORTB_PIN_SIZE			(0x02U)

static const Port_PinConfigType portG_pins[PORT_PORTG_PIN_SIZE] =
{

		{
				PORT_PORTG_PIN13,
				PORT_MODE_GPIO,
				PORT_PIN_OUT,
				PORT_LOW,
				PUSH_PULL,
				PUPD_OFF
		},
		{
				PORT_PORTG_PIN14,
				PORT_MODE_GPIO,
				PORT_PIN_OUT,
				PORT_HIGH,
				PUSH_PULL,
				PUPD_OFF
		}
};
static const Port_PinConfigType portA_pins[PORT_PORTA_PIN_SIZE] =
{

		{
				PORT_PORTA_PIN0,
				PORT_MODE_USB_FS,
				PORT_PIN_AF_OUT,
				PORT_LOW,
				OUT_NOT_ACTIVE,
				PUPD_OFF
		}
		/*,
		Configuration for USART1 TX
		{
				PORT_PORTA_PIN9,
				PORT_AF_USART_1,
				PORT_PIN_AF_OUT,
				PORT_HIGH,
				PUSH_PULL,
				PUPD_OFF
		},
		Configuration for USART1 RX
		{
				PORT_PORTA_PIN10,
				PORT_AF_USART_1,
				PORT_PIN_AF_IN,
				PORT_HIGH,
				OUT_NOT_ACTIVE,
				PUPD_OFF
		}*/
};
static const Port_PinConfigType portB_pins[PORT_PORTB_PIN_SIZE] =
{

		{
				OTG_HS_DP,
				PORT_MODE_USB_FS,
				PORT_PIN_AF_OUT,
				PORT_LOW,
				OUT_NOT_ACTIVE,
				PUPD_OFF
		},
		{
				OTG_HS_DM,
				PORT_MODE_USB_FS,
				PORT_PIN_AF_OUT,
				PORT_LOW,
				OUT_NOT_ACTIVE,
				PUPD_OFF
		}
};
/*TODO : Replace Port_Type with Port_ConfigType*/
static const Port_Type portsConfig[3] =
{
		{
				portG_pins,
				PORT_PORTG_PIN_SIZE
		},
		{
				portA_pins,
				PORT_PORTA_PIN_SIZE
		},
		{
				portB_pins,
				PORT_PORTB_PIN_SIZE
		}

};

Port_ConfigType	portConfig =
{
		portsConfig ,
		2
};
