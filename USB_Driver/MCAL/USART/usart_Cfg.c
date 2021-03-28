#include "usart.h"

UsartConfigType usartConfig[USART_CHANNELS_SIZE]=
{
		{
				LIN_CHANNEL_1,
				USART_DATA_LEN_8,
				USART_ONE_STOP_BIT,
				20000,/*Baud Rate*/
				USART_PARITY_NOT_USED,
				USART_OVER_SAMPLE_16,
				USART_SINGLE_SAMPLE,
				USART_INTERRUPT_TX_EMPTY,
				LIN_MODE
		}
};
