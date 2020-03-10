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
			

int main(void)
{
	//Enable the ADC RCC
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	while(1){

	}
}
