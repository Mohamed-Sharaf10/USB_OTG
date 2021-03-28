
#include "std.h"
#include "DMA_Cfg.h"

#ifndef	_DMA_H
#define _DMA_H
/*
 * DmaChannelType data type represent the number of selected stream
 * !Range : 0 - F
 * */
typedef uint8 DmaChannelType ;

typedef enum {DMA_STREAM_PR_LOW=0x00 ,DMA_STREAM_PR_MED=0x01 ,
			DMA_STREAM_PR_HIGH=0x02 ,DMA_STREAM_PR_V_HIGH=0x03} DmaStreamPriority;
/*
 * !name: DmaPeripheralReq
 * !Description: Data type that holds the peripheral ID which request DMA transfer
 *
 * */
typedef uint8 DmaPeripheralReq;

/*
 * !DEscription: Enable or Disable FIFO
 * !Range:
 * 		STD_ON : FIFO is enabled
 * 		STD_OFF: FIFO is disabled
 */
typedef uint8	DmaFIFOEnable ;
/*
 * !DEscription: Direction of DMA transaction
 * !Range:
 * 		DMA_PREPH_TO_MEM : from peripheral to memory
 * 		DMA_MEM_TO_PERIPH: From memory to peripheral
 * 		DMA_MEM_TO_MEM	 : From memory to memory [ only in case of DMA2]
 * 		STD_OFF: FIFO is disabled
 */
typedef enum {DMA_PERIPH_TO_MEM=0x00 , DMA_MEM_TO_PERIPH=0x01 , DMA_MEM_TO_MEM=0x02} DmaDirectionType;

/*
 * !Description: Base Address of peripheral that will move data from/to it
 */
typedef uint32	DmaPeriPheralAddress ;
/*
* !Description: Base Address of memory that will move data from/to it
*/
typedef uint32	DmaMemoryAddress ;


typedef uint8 DmaTransactionSize ;

/*
 * !Description: Data type define data size of the peripheral
 */
typedef enum {DMA_PER_SIZE_BYTE = 0 , DMA_PER_SIZE_HALF_WORD = 1 ,
				DMA_PER_SIZE_WORD = 2 }DmaPeriphDataSizeType;
/*
 * !Description: Data type define data size of the peripheral
 */

typedef enum {DMA_MEM_SIZE_BYTE = 0 , DMA_MEM_SIZE_HALF_WORD = 1 ,
								DMA_MEM_SIZE_WORD = 2 }DmaMemDataSizeType;

typedef enum{DMA_FIFO_QUARTER=0x00 ,DMA_FIFO_HALF=0x01 ,DMA_FIFO_THREE_QUARTER=0x02,
			DMA_FIFO_FULL=0x03}DmaFIFOThresholdType;

typedef enum{DMA_SINGLE_MODE ,DMA_BURST_MODE}DmaOperationModeType;

typedef enum{DMA_BURST_4_BEATS = 0x01,DMA_BURST_8_BEATS = 0x02,DMA_BURST_16_BEATS= 0x03}DmaBurstSize;
typedef uint32	DmaInterruptType;

#if (DMA_ENABLE_CALLBACK_NOTIFICATION == STD_ON)
/*
 * !Description: Callback notification will be called after transfer complete
 * */
typedef void (*DMA_EndOfTransferNotification)(void) ;
#endif

typedef struct {
	DmaChannelType			           streamNumber ;
	DmaStreamPriority		           streamPriority;
	DmaPeripheralReq		           peripheralReq ;
	DmaFIFOEnable			           fifoEnable ;
	DmaDirectionType		           transactionDir;
	DmaFIFOThresholdType			   fifoThreshold;
	DmaInterruptType					dmaInterrupt ;
	#if(DMA_ENABLE_CALLBACK_NOTIFICATION==STD_ON)
	DMA_EndOfTransferNotification	   notificationCallBack ;
	#endif
	DmaOperationModeType			    dmaMode;
	DmaBurstSize						burstSize;
}Dma_ConfigType;

typedef struct {
	DmaPeriPheralAddress peripheralAddress;
	DmaMemoryAddress memoryAddress;
	DmaTransactionSize transactionSize;
	DmaPeriphDataSizeType periphSize;
	DmaMemDataSizeType memSize;
}Dma_TransactionType;
/*
 * !Description: Data type define the status of the DMA module
 */
typedef enum{DMA_UNINT , DMA_INIT} Dma_StatusType;


typedef enum{DMA_CHANNEL_UNINIT,DMA_CHANNEL_OK,DMA_CHANNEL_CANCEL,DMA_CHENNEL_BUSY,DMA_CHANNEL_DISABLED} Dma_ChannelStatusType;

extern const Dma_ConfigType	dmaConfig[DMA_NUMBER_OF_CHANNELS] ;

void Dma_Init(const Dma_ConfigType* dma_config);

Std_ReturnType Dma_SetupTransfer(DmaChannelType dmaChannel ,const Dma_TransactionType *transactionCfg );

Std_ReturnType Dma_Enable(DmaChannelType streamNumber);

Std_ReturnType Dma_Disable(DmaChannelType streamNumber);
/*Return status of interrupt whether it fired or not*/
uint8 Dma_GetInterruptFlagStatus(DmaChannelType dmaChannel,DmaInterruptType	dmaInterrupt);

void Dma_ClearInterruptFlagStatus(DmaChannelType dmaChannel,DmaInterruptType	dmaInterrupt);

#endif
