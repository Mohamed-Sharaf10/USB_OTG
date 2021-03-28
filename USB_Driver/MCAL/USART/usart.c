#include "usart.h"
#include <math.h>
#define extract_int(x)

typedef struct {
	UsartConfigType 			*usartConfig;
	UsartChannelStatusType		 status;
}UsartInternalConfig;


static void extractManitssaFraction(float usart_div , uint32 *mantissa , float *fraction);
static UsartInternalConfig  ChannelConfigurations[8] ;



void Usart_Init(UsartConfigType *usartConfigArray)
{

	uint8 usart_index ;
    UsartConfigType usartConfig;
    float usart_div ;
    float fractionPart ;
    uint32 div_fraction;
    uint32 mantissa ;
	for(usart_index = 0 ; usart_index<USART_CHANNELS_SIZE ;usart_index++)
	{
		usartConfig = usartConfigArray[usart_index] ;

		/*TODO 1-Enable Clock for specified USART */
		*(usartRCCEn[usartConfig.channelId].registerAddress)|=usartRCCEn[usartConfig.channelId].usartEnableField;
		/*2- Set Frame length*/
		USART_Channels[usartConfig.channelId]->CR1&=~USART_CR1_M;
		USART_Channels[usartConfig.channelId]->CR1|=usartConfig.dataLength;

		/*3- Set Number of stop bits*/
		USART_Channels[usartConfig.channelId]->CR2&=~USART_CR2_STOP;
		USART_Channels[usartConfig.channelId]->CR2|=usartConfig.stopBits;

		/*4- TODO Enable DMA */

		/*5-Select Desired Baud Rate */
		usart_div = ((float)(CLOCK_FREQUENCY)/(8*usartConfig.baudRate*(2-usartConfig.overSampling)));
		extractManitssaFraction(usart_div,&mantissa , &fractionPart);
		if(usartConfig.overSampling==USART_OVER_SAMPLE_16)
		{
			div_fraction = round(fractionPart*16) ;
			USART_Channels[usartConfig.channelId]->BRR = (mantissa<<4) +div_fraction;

		}else
		{
			div_fraction = round(fractionPart*8) ;
			div_fraction = div_fraction > 0x07 ? (div_fraction<< 1) : div_fraction;
			USART_Channels[usartConfig.channelId]->BRR = (mantissa<<4) +div_fraction;
		}
		/*6- Select Parity bits */

		if(usartConfig.parity!=USART_PARITY_NOT_USED)
		{
			USART_Channels[usartConfig.channelId]->CR1|=USART_CR1_PCE;
			USART_Channels[usartConfig.channelId]->CR1&=~USART_CR1_PS ;
			USART_Channels[usartConfig.channelId]->CR1|=usartConfig.parity ;
		}

		/*7- Select OverSampling method*/
		USART_Channels[usartConfig.channelId]->CR1&=~(USART_CR1_OVER8);
		USART_Channels[usartConfig.channelId]->CR1|=(usartConfig.overSampling<<15) ;

		/*8- Select Logic Evaluation Method*/
		USART_Channels[usartConfig.channelId]->CR3&=~(USART_CR3_ONEBIT);
		USART_Channels[usartConfig.channelId]->CR3|=usartConfig.logicEval;

		/*9- Configure required mode*/
		switch(usartConfig.mode)
		{
			case USART_MODE:
				break;
			case LIN_MODE:
				//Clear CLKEN bit
				USART_Channels[usartConfig.channelId]->CR2&=~(USART_CR2_CLKEN);
				//Clear SCEN, HDSEL and IREN in CR2
				USART_Channels[usartConfig.channelId]->CR2&=~(USART_CR3_IREN|USART_CR3_SCEN|USART_CR3_HDSEL);
				//Configure LIN Detection Line Length
				USART_Channels[usartConfig.channelId]->CR2&=~(USART_CR2_LBDL);
				USART_Channels[usartConfig.channelId]->CR2|=(LIN_DETECTION_LENGTH<<5);
				//Set LINEN bit USART_CR2_LINEN
				USART_Channels[usartConfig.channelId]->CR2|=(USART_CR2_LINEN);
				break;
			default:
				break;
		}
		/*10- Configure Interrupts */
		USART_Channels[usartConfig.channelId]->CR1&=~(USART_INTERRUPT_IDLE_FRAME|USART_INTERRUPT_RX_NOT_EMPTY
							|USART_INTERRUPT_TX_COMPLETE|USART_INTERRUPT_TX_EMPTY|USART_INTERRUPT_PARITY_ERROR);
		if(usartConfig.interrupts!=USART_INTERRUPT_NOT_USED)
		{
			USART_Channels[usartConfig.channelId]->CR1|=usartConfig.interrupts;
		}

		/*11 -Enable UART module UE = 1 */
		USART_Channels[usartConfig.channelId]->CR1|=USART_CR1_UE;
		ChannelConfigurations[usartConfig.channelId].usartConfig 	= &usartConfig;
		ChannelConfigurations[usartConfig.channelId].status		= USART_IDLE ;
	}
}
Std_ReturnType USART_Enable(UsartChannelType channel)
{
	if(ChannelConfigurations[channel].status==USART_IDLE)
	{
		USART_Channels[channel]->CR1|=USART_CR1_TE;
		USART_Channels[channel]->CR1|=USART_CR1_RE;
		return E_OK;
	}else
	{
			return E_NOT_OK;
	}
}


Std_ReturnType USART_Transmit(UsartChannelType channel,UsartDataType data )
{
	if(ChannelConfigurations[channel].status==USART_IDLE)
	{
		USART_Channels[channel]->DR = data ;
		ChannelConfigurations[channel].status = USART_BUSY;

#if USART_TX_EMPTY_INTERRUPT==STD_OFF
		/*Synchronous method*/
		while(!(USART_Channels[channel]->SR&USART_SR_TXE));

		ChannelConfigurations[channel].status =USART_IDLE;
#endif
		return E_OK;
	}else
	{
		return E_NOT_OK;
	}
}
UsartErrorType USART_Receive(UsartChannelType channel ,UsartDataType * data)
{
	#if USART_RX_INTERRUPT == STD_OFF
	/*Use of pooling method*/
	while(!(USART_Channels[channel]->SR&USART_SR_RXNE));

	*data = (UsartDataType)USART_Channels[channel]->DR;
	return (USART_Channels[channel]->SR&0x000F);
	#endif
}
static void extractManitssaFraction(float usart_div , uint32 *mantissa , float *fraction)
{
  *mantissa = (uint32) usart_div;
  *fraction = usart_div - *mantissa ;
}

void usart_interruptCallback(UsartChannelType channel)
{
#if USART_TX_EMPTY_INTERRUPT== STD_ON

	if(USART_Channels[channel]->CR1&USART_INTERRUPT_TX_EMPTY)
	{
		ChannelConfigurations[channel].status =USART_IDLE;
	}
#endif
}

void usart_main(void)
{
	/*If pooling method was selected*/
#if USART_TX_EMPTY_INTERRUPT==STD_OFF
	/*
	uint8 usartChannelIndex ;
	for(usartChannelIndex = 0 ; usartChannelIndex<USART_CHANNELS_SIZE ; USART_CHANNELS_SIZE++)
	{
		if(USART_Channels[channel]->CR1&USART_INTERRUPT_TX_EMPTY)
		{
			ChannelConfigurations[channel].status =USART_IDLE;
		}
	}
	*/
#endif

#if USART_LIN_BREAK_DETECT_POLLING==STD_ON
	if((USART_Channels[LIN_CHANNEL_1]->SR)&USART_SR_LBD)
	{
		lin_BreakDetected();
	}
#endif
}
