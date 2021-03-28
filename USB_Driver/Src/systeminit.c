/*
 * systeminit.c
 *
 *  Created on: Jan 3, 2021
 *      Author: msharaf
 */
#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"
#include "Helper/logger.h"

LogLevel system_log_level = LOG_LEVEL_DEBUG;
uint32_t SystemCoreClock=75000000;

static void configure_clock();

void SystemInit(void)
{
	configure_clock();
}

static void configure_clock()
{

	MODIFY_REG(FLASH->ACR,FLASH_ACR_LATENCY,FLASH_ACR_LATENCY_2WS);

	// Enable HSE
	SET_BIT(RCC->CR,RCC_CR_HSEON);

	while(!READ_BIT(RCC->CR,RCC_CR_HSERDY));

	// 1- Select HSE as an input source for the PLL

	SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLLSRC_HSE);
	// 2- Configure PLL (M,N,P,Q) parameters ( Q = 3 , P = 2 , M = 4 , N = 72 )

	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLQ|RCC_PLLCFGR_PLLP|RCC_PLLCFGR_PLLM|RCC_PLLCFGR_PLLN,
			_VAL2FLD(RCC_PLLCFGR_PLLQ,3)|_VAL2FLD(RCC_PLLCFGR_PLLM,4)|_VAL2FLD(RCC_PLLCFGR_PLLN,72));

	// 3- Enable PLL after configured then Wait till PLL is ready
	SET_BIT(RCC->CR,RCC_CR_PLLON);
	// 5- Configure the prescaler APB1 = 2
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE2,_VAL2FLD(RCC_CFGR_PPRE2,4));

	while(!READ_BIT(RCC->CR,RCC_CR_PLLRDY));

	// 4- Switch the main CLK source to be PLL
	MODIFY_REG(RCC->CFGR,RCC_CFGR_SW,_VAL2FLD(RCC_CFGR_SW,RCC_CFGR_SW_PLL));

	// 6- Wait till the main clock switch to PLL

	while(READ_BIT(RCC->CFGR,RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL);
	// 7- Disable the HSI for power saving
	CLEAR_BIT(RCC->CR,RCC_CR_HSION);

}
