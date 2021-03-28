#include "mcu_driver.h"
GPIO_TypeDef * GPIOs[]=
{
		GPIOA ,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOG,
		GPIOH,
		GPIOI,
		GPIOJ,
		GPIOK
};

DMA_Stream_TypeDef *DMA_Channels[] =
{
		DMA1_Stream0,
		DMA1_Stream1,
		DMA1_Stream2,
		DMA1_Stream3,
		DMA1_Stream4,
		DMA1_Stream5,
		DMA1_Stream6,
		DMA1_Stream7,
		DMA2_Stream0,
		DMA2_Stream1,
		DMA2_Stream2,
		DMA2_Stream3,
		DMA2_Stream4,
		DMA2_Stream5,
		DMA2_Stream6,
		DMA2_Stream7,
};
DMA_TypeDef * DMA_Controllers[2]=
{
		DMA1,
		DMA2
};

USART_TypeDef * USART_Channels[] =
{
		USART1,
		USART2,
		USART3,
		UART4,
		UART5,
		USART6,
		UART7,
		UART8
};

const UsartEnRCCType usartRCCEn[8] =
{
		{
				&(RCC->APB2ENR), //USART1 enable clock register
				RCC_APB2ENR_USART1EN //USART1 enable clock field
		},
		{
				&(RCC->APB1ENR),  //USART2 enable clock register
				RCC_APB1ENR_USART2EN  //USART2 enable clock field
		},
		{
				&(RCC->APB1ENR),		//USART3 enable clock register
				RCC_APB1ENR_USART3EN //USART3 enable clock field
		},
		{
				&(RCC->APB1ENR),		//UART4 enable clock register
				RCC_APB1ENR_UART4EN //UART4 enable clock field
		},
		{
				&(RCC->APB1ENR),		//UART5 enable clock register
				RCC_APB1ENR_UART5EN //UART5 enable clock field
		},
		{
				&(RCC->APB2ENR), //USART6 enable clock register
				RCC_APB2ENR_USART6EN //USART6 enable clock field
		},
		{
				&(RCC->APB1ENR),		//UART7 enable clock register
				RCC_APB1ENR_UART7EN //UART7 enable clock field
		},
		{
				&(RCC->APB1ENR),		//UART8 enable clock register
				RCC_APB1ENR_UART8EN //UART8 enable clock field
		}
};

