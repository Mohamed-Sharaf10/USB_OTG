#include "stm32f4xx.h"

#ifndef  _MCU_DRIVER_H
#define  _MCU_DRIVER_H
/*Pin Number fields*/
#define PORT_PIN_MASK				(0x0FU)

#define PORT_FIELD_MASK				(0xF0U)

#define PIN_MODER_PUPD_FIELD(pin)		(0x11<<(2*(pin)))


#define CLOCK_FREQUENCY			90000000
/*Array of GPIOs for STM32F*/
extern GPIO_TypeDef * GPIOs[11] ;

extern DMA_Stream_TypeDef * DMA_Channels[16] ;
extern DMA_TypeDef * DMA_Controllers[2];

extern USART_TypeDef * USART_Channels[8];

/*USART_EN clock data structure*/

typedef struct {
	volatile uint32_t *registerAddress; //Can be &RCC_APB2ENR or &RCC_APB1ENR
	uint32_t	usartEnableField; //Field of corresponding usart bit e.g for bit 4 field will be 0x00000010
}UsartEnRCCType;

extern const UsartEnRCCType usartRCCEn[8];

#endif

