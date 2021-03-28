#include "DMA.h"

static Dma_StatusType		DMA_status = DMA_UNINT;
static Dma_ChannelStatusType	channelStatus[16]={DMA_CHANNEL_UNINIT};

#if (DMA_ENABLE_CALLBACK_NOTIFICATION == STD_ON)
static DMA_EndOfTransferNotification	dmaEndOfTranCallbacks[16];
#endif

#define DMA_CONTROLLER_ID_FIELD   (0x08)
void Dma_Init(const Dma_ConfigType* dma_config)
{
	uint8 streamIndex ;
	Dma_ConfigType dmaConfigTmp;

	/*Enable clock for DMA controller*/
	RCC->AHB1ENR|=(RCC_AHB1ENR_DMA1EN|RCC_AHB1ENR_DMA2EN);
	 /*First you have to clear all interrupt flags */
	if((dmaConfigTmp.streamNumber&(~DMA_CONTROLLER_ID_FIELD))<3)
	{ /*Use DMA_LISR for streams from 0 to 3*/
		DMA_Controllers[(dmaConfigTmp.streamNumber&DMA_CONTROLLER_ID_FIELD)>>3]->LIFCR|=0x0F7D0F7D;
	}else
	{
		/*Use DMA_HISR for streams from 4 to 7*/
		DMA_Controllers[(dmaConfigTmp.streamNumber&DMA_CONTROLLER_ID_FIELD)>>3]->HIFCR|=0x0F7D0F7D;
	}
	for(streamIndex = 0 ; streamIndex<DMA_NUMBER_OF_CHANNELS;streamIndex++)
	{
		dmaConfigTmp = dma_config[streamIndex];
		/*1- Check if stream is enabled then disable it*/
		if((DMA_Channels[dmaConfigTmp.streamNumber]->CR&DMA_SxCR_EN)==1)
		{
			/*Clear enable bit then wait till the last transfer complete*/
			DMA_Channels[dmaConfigTmp.streamNumber]->CR&=~DMA_SxCR_EN ;
			while((DMA_Channels[dmaConfigTmp.streamNumber]->CR&DMA_SxCR_EN));
		}
		/*2- Select DMA channel that will request transmission*/
			/*In case of memory to memory transmission no need to configure it*/
		if(dmaConfigTmp.transactionDir!=DMA_MEM_TO_MEM)
		{
			DMA_Channels[dmaConfigTmp.streamNumber]->CR&=~DMA_SxCR_CHSEL;
			DMA_Channels[dmaConfigTmp.streamNumber]->CR|=(dmaConfigTmp.peripheralReq<<25);
		}
		/*3- Configure Stream Priority Register*/
		DMA_Channels[dmaConfigTmp.streamNumber]->CR&=~DMA_SxCR_PL;
		DMA_Channels[dmaConfigTmp.streamNumber]->CR|=(dmaConfigTmp.streamPriority<<16);

		/*4- Configure FIFO buffer [ enable/disable - threshold value]*/
		if(dmaConfigTmp.fifoEnable==STD_ON)
		{
			DMA_Channels[dmaConfigTmp.streamNumber]->FCR|=DMA_SxFCR_DMDIS;
			/*Configure DMA threshold Value*/
			DMA_Channels[dmaConfigTmp.streamNumber]->FCR&=~DMA_SxFCR_FTH;
			DMA_Channels[dmaConfigTmp.streamNumber]->FCR|=dmaConfigTmp.fifoThreshold;
		}
		else if(dmaConfigTmp.fifoEnable==STD_OFF)
		{
			DMA_Channels[dmaConfigTmp.streamNumber]->FCR&=~DMA_SxFCR_DMDIS;
		}else
		{
			/*Report error [Wrong parameter value]*/
		}
		/*5-Configure Data transfer direction*/
		DMA_Channels[dmaConfigTmp.streamNumber]->CR&=~DMA_SxCR_DIR;
		DMA_Channels[dmaConfigTmp.streamNumber]->CR|=(dmaConfigTmp.transactionDir<<6);

		  /* Select peripheral and memory incremented mode */
		DMA_Channels[dmaConfigTmp.streamNumber]->CR|= DMA_SxCR_PINC;
		DMA_Channels[dmaConfigTmp.streamNumber]->CR|= DMA_SxCR_MINC;

		/*Configure DMA interrupts*/
		DMA_Channels[dmaConfigTmp.streamNumber]->CR|=dmaConfigTmp.dmaInterrupt ;
		channelStatus[dmaConfigTmp.streamNumber]=DMA_CHANNEL_DISABLED;

		/*Configure DMA burst mode*/

		if(dmaConfigTmp.dmaMode==DMA_BURST_MODE)
		{
			if(dmaConfigTmp.transactionDir!=DMA_MEM_TO_PERIPH)
			{
				DMA_Channels[dmaConfigTmp.streamNumber]->CR&=~DMA_SxCR_PBURST;
				DMA_Channels[dmaConfigTmp.streamNumber]->CR|=(dmaConfigTmp.burstSize<<21);

			}else
			{
				DMA_Channels[dmaConfigTmp.streamNumber]->CR&=~DMA_SxCR_MBURST;
				DMA_Channels[dmaConfigTmp.streamNumber]->CR|=(dmaConfigTmp.burstSize<<23);

			}
		}

		#if (DMA_ENABLE_CALLBACK_NOTIFICATION == STD_ON)
		dmaEndOfTranCallbacks[dmaConfigTmp.streamNumber]=dmaConfigTmp.notificationCallBack;
		#endif
	}
	DMA_status =DMA_INIT ;
}

Std_ReturnType Dma_SetupTransfer(DmaChannelType dmaChannel ,const Dma_TransactionType *transactionCfg )
{
	if(DMA_status==DMA_INIT&&channelStatus[dmaChannel]==DMA_CHANNEL_DISABLED&&(DMA_Channels[dmaChannel]->CR&DMA_SxCR_EN)==0)
	{
		// Set peripheral port address [error prone]
		DMA_Channels[dmaChannel]->PAR=transactionCfg->peripheralAddress;
		// Set memory port address [error prone]
		DMA_Channels[dmaChannel]->M0AR=transactionCfg->memoryAddress ;
		// Set Number of transaction
		DMA_Channels[dmaChannel]->NDTR=transactionCfg->transactionSize;
		// Set peripheral data size [word - half word - byte]
		DMA_Channels[dmaChannel]->CR&=~DMA_SxCR_PSIZE;
		DMA_Channels[dmaChannel]->CR|=((transactionCfg->periphSize)<<11);
		// Set memory data size [word - half word - byte]
		DMA_Channels[dmaChannel]->CR&=~DMA_SxCR_MSIZE;
		DMA_Channels[dmaChannel]->CR|=((transactionCfg->memSize)<<13);

	}else
	{
		return E_NOT_OK;
	}
	return E_OK;
}
Std_ReturnType Dma_Enable(DmaChannelType dmaChannel)
{
	if(DMA_status==DMA_INIT&&channelStatus[dmaChannel]==DMA_CHANNEL_DISABLED)
	{
		/*Clear all Event flags */
		 /*First you have to clear all interrupt flags */
		if((dmaChannel&(~DMA_CONTROLLER_ID_FIELD))<3)
		{ /*Use DMA_LISR for streams from 0 to 3*/
			DMA_Controllers[(dmaChannel&DMA_CONTROLLER_ID_FIELD)>>3]->LIFCR|=0x0F7D0F7D;
		}else
		{
			/*Use DMA_HISR for streams from 4 to 7*/
			DMA_Controllers[(dmaChannel&DMA_CONTROLLER_ID_FIELD)>>3]->HIFCR|=0x0F7D0F7D;
		}

		DMA_Channels[dmaChannel]->CR|=DMA_SxCR_EN;
	}
	else
	{
		return E_NOT_OK;
	}

	return E_OK;
}

Std_ReturnType Dma_Disable(DmaChannelType dmaChannel)
{
	if(DMA_status==DMA_INIT&&channelStatus[dmaChannel]!=DMA_CHANNEL_DISABLED)
	{
		DMA_Channels[dmaChannel]->CR&=~DMA_SxCR_EN;
		while((DMA_Channels[dmaChannel]->CR&DMA_SxCR_EN));
	}
	else
	{
		return E_NOT_OK;
	}
	return E_OK;
}

uint8 Dma_GetInterruptFlagStatus(DmaChannelType dmaChannel,DmaInterruptType	dmaInterrupt)
{

	if(DMA_Controllers[(dmaChannel&DMA_CONTROLLER_ID_FIELD)>>3]->LISR&dmaInterrupt)
	{
		return STD_ON;
	}
	else
	{
		return STD_OFF;
	}
}

void Dma_ClearInterruptFlagStatus(DmaChannelType dmaChannel,DmaInterruptType	dmaInterrupt)
{
	DMA_Controllers[(dmaChannel&DMA_CONTROLLER_ID_FIELD)>>3]->LIFCR|=(dmaInterrupt);
}
