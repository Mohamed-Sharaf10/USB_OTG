#include "Delay.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

void Delay_Init()
{
	SysTick_Config((SystemCoreClock/1000));
	NVIC_SetPriority(SysTick_IRQn,0);
}
void ms_delay(uint32_t delayMs)
{
	uint32_t startTickCounter = get_SysTick();

	while((get_SysTick()-startTickCounter)<delayMs);
}
