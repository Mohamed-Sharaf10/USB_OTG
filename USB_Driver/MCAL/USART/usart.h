
#ifndef _USART_H
#define _USART_H

#include "std.h"
#include "usart_Cfg.h"
#include "lin_Cbk.h"
#include "lin_cfg.h"
/*Data type for channel ID */
typedef uint8  UsartChannelType ;
/*USART configuration for STM32f429 target [8 Channels]*/
#define USART_CHANNEL_1		(0x00)
#define USART_CHANNEL_2		(0x01)
#define USART_CHANNEL_3		(0x02)
#define USART_CHANNEL_4		(0x03)
#define USART_CHANNEL_5		(0x04)
#define USART_CHANNEL_6		(0x05)
#define USART_CHANNEL_7		(0x06)
#define USART_CHANNEL_8		(0x07)


/*Data type for length of data to be sent*/
typedef enum {USART_DATA_LEN_8= 0x0000 , USART_DATA_LEN_9 = 0x1000 }UsartDataLengthType;
/*Data type for length of data to be sent*/
typedef enum {USART_ONE_STOP_BIT=0x0000 , USART_HALF_STOP_BIT = 0x1000,
	           USART_TWO_STOP_BIT = 0x2000 , USART_ONE_HALF_STOP_BIT =0x3000}UsartStopBitsNumType;
/*Data type for OverSampling method*/
typedef enum {USART_OVER_SAMPLE_16 = (0x00),USART_OVER_SAMPLE_8 = (0x01)} UsartOverSamplingType;

typedef enum {USART_MAJORITY_VOTE = (0x00) ,USART_SINGLE_SAMPLE=USART_CR3_ONEBIT} UsartLogicEvalType ;

typedef enum {USART_EVEN_PARITY = (0x00) ,USART_ODD_PARITY =USART_CR1_PS , USART_PARITY_NOT_USED}UsartParityType;


typedef enum{USART_MODE ,LIN_MODE ,SMART_CARD_MODE }UsartModeType;
/*Data type represent Baud Rate */
typedef uint32	UsartBaudRateType;

/*!Description: USART Interrupt Data type*/
typedef uint32	UsartInterruptType;
#define	USART_INTERRUPT_IDLE_FRAME			USART_CR1_IDLEIE
#define USART_INTERRUPT_RX_NOT_EMPTY		USART_CR1_RXNEIE
#define	USART_INTERRUPT_TX_COMPLETE			USART_CR1_TCIE
#define	USART_INTERRUPT_TX_EMPTY			USART_CR1_TXEIE
#define	USART_INTERRUPT_PARITY_ERROR		USART_CR1_PEIE
#define USART_INTERRUPT_NOT_USED			(0x00000000U)
/**/
typedef uint8 UsartDataType;

typedef enum {USART_UNINIT ,USART_BUSY , USART_IDLE} UsartChannelStatusType;

typedef uint16 UsartErrorType;

#define USART_PARITY_ERROR			(0x0001U)
#define USART_FRAME_ERROR			(0x0002U)
#define USART_NOISE_ERROR			(0x0004U)
#define USART_OVERRUN_ERROR			(0x0008U)


typedef struct {
	UsartChannelType		channelId ;
	UsartDataLengthType		dataLength;
	UsartStopBitsNumType	stopBits;
	UsartBaudRateType		baudRate ;
	UsartParityType			parity ;
	UsartOverSamplingType	overSampling;
	UsartLogicEvalType		logicEval ;
	UsartInterruptType      interrupts;
	UsartModeType			mode ;
	/*Further specs related to USART*/
}UsartConfigType;


extern UsartConfigType usartConfig[USART_CHANNELS_SIZE];
/*Init function */

void Usart_Init(UsartConfigType *usartConfig);
/*Transmit data over Usart channel*/
Std_ReturnType USART_Transmit(UsartChannelType channel,UsartDataType data ) ;


/*Receive data from */
UsartErrorType USART_Receive(UsartChannelType channel ,UsartDataType * data);


/*Transmit array of data */
Std_ReturnType USART_TransmitArray(UsartChannelType channel , const UsartDataType *Buffer , uint8 maxSize);


/*Receive array of data */
Std_ReturnType USART_ReceiveArray(UsartChannelType channel , UsartDataType *Buffer , uint8 maxSize);


Std_ReturnType USART_Enable(UsartChannelType channel);


void usart_interruptCallback(UsartChannelType channel);


/*Usart Main function*/

void usart_main(void);
#endif
