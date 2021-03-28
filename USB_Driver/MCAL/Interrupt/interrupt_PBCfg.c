/*
 * int_Cfg.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Mohamed Sharaf
 */
#include "interrupt.h"

InterruptType_Def interrupts[INTERRUPTS_SIZE] =
{

		{
				CAN1_TX_IRQn,
				IRQ_ON,
				INTERRUPT_PRIORITY_0
		}
};
