/*
 * int.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Mohamed Sharaf
 */

#include "interrupt.h"

void Interrupt_init(const InterruptType_Def *interrupts ,PriorityGroup priorityGroup)
{
	uint8_t interruptIndex = 0 ;
 // 1- Set Priority Group
	NVIC_SetPriorityGrouping(priorityGroup);
 // 2- Initialize each interrupt in the system
	for(;interruptIndex < INTERRUPTS_SIZE ; interruptIndex++)
	{
		// 3 - Configure priority for interrupt
		NVIC_SetPriority(interrupts[interruptIndex].interruptNum,interrupts[interruptIndex].priority);
		// 4 -Enable or diable interrupt
		if(interrupts[interruptIndex].enable==IRQ_ON)
		{
			NVIC_EnableIRQ(interrupts[interruptIndex].interruptNum);
		}else if(interrupts[interruptIndex].enable==IRQ_OFF)
		{
			NVIC_DisableIRQ(interrupts[interruptIndex].interruptNum);
		}
	}
}

void Interrupt_enable(IRQn_Type interruptNum )
{
	NVIC_EnableIRQ(interruptNum);
}
void Interrupt_disable(IRQn_Type interruptNum )
{
	NVIC_DisableIRQ(interruptNum);

}
void Interrupt_SetPending(IRQn_Type interruptNum)
{
	NVIC_SetPendingIRQ(interruptNum);
}
