/*
 * int_Cfg.h
 *
 *  Created on: Jan 24, 2020
 *      Author: Mohamed Sharaf
 */

#ifndef INC_INT_CFG_H_
#define INC_INT_CFG_H_

#define INTERRUPTS_SIZE			(0x01)


			/*				Priority groups				 */
#define INTERRUPT_PRIORITY_GROUP_0		(0x00000003) 	// Group priorities = 16 , Sub priorities = 0
#define INTERRUPT_PRIORITY_GROUP_1		(0x00000004)	// Group priorities = 8 , Sub priorities = 2
#define INTERRUPT_PRIORITY_GROUP_2		(0x00000005)	// Group priorities = 4 , Sub priorities = 4
#define INTERRUPT_PRIORITY_GROUP_3		(0x00000006)	// Group priorities = 2 , Sub priorities = 8
#define INTERRUPT_PRIORITY_GROUP_4		(0x00000007)	// Group priorities = 0 , Sub priorities = 16


		/*				Priority numbers					*/
#define INTERRUPT_PRIORITY_0		(0x00000000)
#define INTERRUPT_PRIORITY_1		(0x00000001)
#define INTERRUPT_PRIORITY_2		(0x00000002)
#define INTERRUPT_PRIORITY_3		(0x00000003)
#define INTERRUPT_PRIORITY_4		(0x00000004)
#define INTERRUPT_PRIORITY_5		(0x00000005)
#define INTERRUPT_PRIORITY_6		(0x00000006)
#define INTERRUPT_PRIORITY_7		(0x00000007)
#define INTERRUPT_PRIORITY_8		(0x00000008)
#define INTERRUPT_PRIORITY_9		(0x00000009)
#define INTERRUPT_PRIORITY_10		(0x0000000A)
#define INTERRUPT_PRIORITY_11		(0x0000000B)
#define INTERRUPT_PRIORITY_12		(0x0000000C)
#define INTERRUPT_PRIORITY_13		(0x0000000D)
#define INTERRUPT_PRIORITY_14		(0x0000000E)
#define INTERRUPT_PRIORITY_15		(0x0000000F)
#define INTERRUPT_PRIORITY_16		(0x00000010)

	/* Symbolic names for used interrupts */

#define	GREEN_LED_IRQ_ON		(EXTI0_IRQn)
#define GREEN_LED_IRQ_OFF		(EXTI1_IRQn)
#define RED_LED_IRQ_ON			(EXTI2_IRQn)
#define RED_LED_IRQ_OFF			(EXTI3_IRQn)



#endif /* INC_INT_CFG_H_ */
