#include "std.h"
#include "mcu_driver.h"
#ifndef _DMA_CFG_H
#define _DMA_CFG_H
#define DMA_NUMBER_OF_CHANNELS	(0x01)
#define DMA_ENABLE_CALLBACK_NOTIFICATION	STD_OFF
/*Symbolic names for stream numbers */
#define DMA1_CHANNEL_0		(0x00U)
#define DMA1_CHANNEL_1		(0x01U)
#define DMA1_CHANNEL_2		(0x02U)
#define DMA1_CHANNEL_3		(0x03U)
#define DMA1_CHANNEL_4		(0x04U)
#define DMA1_CHANNEL_5		(0x05U)
#define DMA1_CHANNEL_6		(0x06U)
#define DMA1_CHANNEL_7		(0x07U)
#define DMA2_CHANNEL_0		(0x08U)
#define DMA2_CHANNEL_1		(0x09U)
#define DMA2_CHANNEL_2		(0x0AU)
#define DMA2_CHANNEL_3		(0x0BU)
#define DMA2_CHANNEL_4		(0x0CU)
#define DMA2_CHANNEL_5		(0x0DU)
#define DMA2_CHANNEL_6		(0x0EU)
#define DMA2_CHANNEL_7		(0x0FU)
/*Symbolic names for stream peripherals names */
#define	DMA1_STREM_0_SPI3_RX				(0x00U)
#define	DMA1_STREM_0_I2C1_RX				(0x01U)
#define	DMA1_STREM_0_TIM4_CH1				(0x02U)
#define	DMA1_STREM_0_I2S3_EXT_RX			(0x03U)
#define	DMA1_STREM_0_UART5_RX				(0x04U)
#define	DMA1_STREM_0_UART8_TX				(0x05U)
#define	DMA1_STREM_0_TIM5_CH3_TIM5_UP		(0x06U)
#define	DMA1_STREM_1_TIM2_UP_TIM2_CH3		(0x03U)
#define	DMA1_STREM_1_USART3_RX				(0x04U)
#define	DMA1_STREM_1_UART7_TX				(0x05U)
#define	DMA1_STREM_1_TIM5_CH4_TIM5_TRIG		(0x06U)
#define	DMA1_STREM_1_TIM6_UP				(0x07U)
#define	DMA1_STREM_2_SPI3_RX				(0x00U)
#define	DMA1_STREM_2_TIM7_UP				(0x01U)
#define	DMA1_STREM_2_I2S3_EXT_RX			(0x02U)
#define	DMA1_STREM_2_2C3_RX					(0x03U)
#define	DMA1_STREM_2_UART4_RX				(0x04U)
#define	DMA1_STREM_2_TIM3_CH4_TIM3_UP		(0x05U)
#define	DMA1_STREM_2_TIM5_CH1				(0x06U)
#define	DMA1_STREM_2_I2C2_RX				(0x07U)
#define	DMA1_STREM_3_SPI2_RX				(0x00U)
#define	DMA1_STREM_3_TIM4_CH2				(0x02U)
#define	DMA1_STREM_3_I2S2_EXT_RX			(0x03U)
#define	DMA1_STREM_3_USART3_TX				(0x04U)
#define	DMA1_STREM_3_UART7_RX				(0x05U)
#define	DMA1_STREM_3_TIM5_CH4_TIM5_TRIG		(0x06U)
#define	DMA1_STREM_3_I2C2_RX				(0x07U)
#define	DMA1_STREM_5_SPI3_TX				(0x00U)
#define	DMA1_STREM_5_I2C1_RX				(0x01U)
#define	DMA1_STREM_5_I2S3_EXT_TX			(0x02U)
#define	DMA1_STREM_5_TIM2_CH1				(0x03U)
#define	DMA1_STREM_5_USART2_RX				(0x04U)
#define	DMA1_STREM_5_TIM3_CH2				(0x05U)
#define	DMA1_STREM_5_DAC1					(0x07U)
#define	DMA1_STREM_6_I2C1_TX				(0x01U)
#define	DMA1_STREM_6_TIM4_UP				(0x02U)
#define	DMA1_STREM_6_TIM2_CH2_TIM2_CH4		(0x03U)
#define	DMA1_STREM_6_USART2_TX				(0x04U)
#define	DMA1_STREM_6_UART8_RX				(0x05U)
#define	DMA1_STREM_6_TIM5_UP				(0x06U)
#define	DMA1_STREM_6_DAC2					(0x07U)
#define	DMA1_STREM_7_SPI3_TX				(0x00U)
#define	DMA1_STREM_7_I2C1_TX				(0x01U)
#define	DMA1_STREM_7_TIM4_CH3				(0x02U)
#define	DMA1_STREM_7_TIM2_UP_TIM2_CH4		(0x03U)
#define	DMA1_STREM_7_UART5_TX				(0x04U)
#define	DMA1_STREM_7_TIM3_CH3				(0x05U)
#define	DMA1_STREM_7_I2C2_TX				(0x07U)
#define DMA2_STREAM_X_SW					(0xFFU) /*Used in case of memory to memory transfer because no peripheral request is needed */


/*DMA interrupt types*/
#define DMA_DIRECT_MODE_ERROR_INTERRUPT		DMA_SxCR_DMEIE
#define DMA_TRANSFER_ERROR_INTERRUPT		DMA_SxCR_TEIE
#define	DMA_HALF_TRANSFER_INTERRUPT			DMA_SxCR_HTIE
#define DMA_TRANSFER_COMPLETE_INTERRUPT		DMA_SxCR_TCIE

#endif
