#include "stm32f10x.h"

void setup_led_timer(int ccr1, int ccr3, int ccr4)
{
	//TIM4->CCR1  = 0;       // 0
	//TIM4->CCR3  = 5000;    //
	//TIM4->CCR4  = 2500;    //
	TIM4->CCR1  = ccr1;       // 0
	TIM4->CCR3  = ccr3;    //
	TIM4->CCR4  = ccr4;    //
	
	TIM4->CCMR2 = 0x6060;  // 0x6060
	
	TIM4->CCER  = 0x1110;  // 0x1100 set capture/compare enable register
	TIM4->SMCR  = 0;       // 0 set slave mode control register
	
	TIM4->CR1 = 1u<<2;    // 1: URS: Only counter overflow/underflow
		 // generates an update interrupt or DMA
		 // request if enabled.

	TIM4->CR2 = 0;        // 0x0 set command register 2

	TIM4->CR1 |= 1u<<0;   // 0: enable timer
}