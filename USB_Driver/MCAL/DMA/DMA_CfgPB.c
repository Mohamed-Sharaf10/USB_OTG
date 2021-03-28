#include "DMA.h"

const Dma_ConfigType	dmaConfig[DMA_NUMBER_OF_CHANNELS]  =
{
		{
				DMA2_CHANNEL_0,
				DMA_STREAM_PR_HIGH,
				DMA2_STREAM_X_SW,/*Used for memory to memory transfer*/
				STD_ON ,/*Enable FIFO*/
				DMA_MEM_TO_MEM,
				DMA_FIFO_FULL,
				DMA_TRANSFER_COMPLETE_INTERRUPT,
				DMA_BURST_MODE,
				DMA_BURST_4_BEATS
		}

};
