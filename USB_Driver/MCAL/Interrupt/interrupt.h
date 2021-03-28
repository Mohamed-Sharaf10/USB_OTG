/*
 * int.h
 *
 *  Created on: Jan 24, 2020
 *      Author: Mohamed Sharaf
 */

#ifndef INC_INT_H_
#define INC_INT_H_

#include "stm32f4xx.h"
#include "interrupt_Cfg.h"




typedef uint32_t  PriorityGroup ;


typedef uint32_t  IRQpriority ;

typedef enum {IRQ_ON , IRQ_OFF}	IRQen_Type;


typedef struct {

	IRQn_Type interruptNum ;
	IRQen_Type enable ; /*Enable interrupt*/
	IRQpriority priority ;

}InterruptType_Def;


extern InterruptType_Def interrupts[INTERRUPTS_SIZE] ;

void Interrupt_init(const InterruptType_Def *interrupts ,PriorityGroup priorityGroup);

void Interrupt_enable(IRQn_Type interruptNum );
void Interrupt_disable(IRQn_Type interruptNum );

void Interrupt_SetPending(IRQn_Type interruptNum);
#endif /* INC_INT_H_ */
