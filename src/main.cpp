/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"

#define PSC_VALUE 640
#define ARR_VALUE 65535

uint32_t counter = 0;


extern "c" void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF){
		counter++;

		TIM2->SR &= ~(TIM_SR_UIF);
	}

}

int main(void)
{
	//-------------STSTEM CLOCK CONFIGURATION-------------------------

	//SET FLASH MEMORY LATENCY AND ENABLE PREFETCH
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
	FLASH->ACR |= FLASH_ACR_PRFTEN;

	//Enable HSI
	RCC->CR |= RCC_CR_HSION;
	//check if HSI is ready
	while(!(RCC->CR & (1<<1))){}
	//set PLL SOURCE to HSI
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
	//set Division factor for the main PLL division clock to 8
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;
	//set main PLL multiplication factor to 168
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_5;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7;
	//set PLL division factor for main system clock to 2
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;

	//Set APB1 clock frequency to 42MHz(prescaler of 4)
	RCC->CFGR &= ~RCC_CFGR_PPRE1;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	//Set APB2 clock frequency to 84MHz(prescaler of 2)
	RCC->CFGR &= ~RCC_CFGR_PPRE2;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	//Enable PLL
	RCC->CR |= RCC_CR_PLLON;
	//check if PLL is ready
	while(!(RCC->CR & (1<<25))){}
	//Select PLL as system clock
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	//check to confirm PLL being used
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL )){}

//-----------------------------------------------------------
//---------configure timer for delay---------------------------
	//enable timer RCC
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Set prescaler value
	TIM2->PSC = PSC_VALUE;
	//Set auto-reload value
	TIM2->ARR = ARR_VALUE;
	//Enable Auto preload
	TIM2->CR1 |= TIM_CR1_ARPE;
	//Set direction to upcounter
	TIM2->CR1 &= ~TIM_CR1_DIR;
	//Set update request_source;
	TIM2->CR1 |= TIM_CR1_URS;
	//generate an update
	TIM2->EGR |= TIM_EGR_UG;
	//Enable update interrupt
	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM2_IRQn,0x00);
	NVIC_EnableIRQ(TIM2_IRQn);











//-----------------------------------------------------------------
	//Enable the ADC RCC
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	//Set GPIO pin to analog mode(GPIOA PIN1)
	GPIOA->MODER |= GPIO_MODER_MODER1;


	while(1){

	}
}
