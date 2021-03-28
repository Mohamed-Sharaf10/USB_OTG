#ifndef _USART_CFG_H
#define _USART_CFG_H

#include "std.h"

/*Number of USART channel*/
#define USART_CHANNELS_SIZE		(0x01)

#define USART_TX_EMPTY_INTERRUPT			(STD_OFF)

#define USART_RX_INTERRUPT					(STD_OFF)

#define LIN_CHANNEL_1						(USART_CHANNEL_1)
#define USART_LIN_BREAK_DETECT_POLLING		(STD_ON)
#endif
