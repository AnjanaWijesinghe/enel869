#include "stm32f10x.h"


void enable_timer(int timer, int psc, int arr)
{
	if(timer == 1)
	{
		// timer 1 is used for delay functions
		// does not use arr
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //0x0800;  // setup timer 1 bus
		TIM1->PSC = (psc-1);  	
		
		//TIM1->PSC = (psc-1);  	
		//TIM1->PSC = (72-1);  //set presclar to 72 
		//TIM1->ARR = (10000-1);  //set auto reload to 10,000
		//TIM1->CR1 |= 1;  // enable counter	
	}
	else if(timer == 4)
	{
		// timer 4 is used for the servo motor
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;  // enable TIM4
		TIM4->PSC = (psc-1);  	
		
		TIM4->ARR = arr;  // setting ARR to 40000 clks
		TIM4->CCR2  = arr/2;       // setting to half the width of ARR
		TIM4->CCR3  = 5000;    //
		TIM4->CCR4  = 2500;    //
		TIM4->CCMR1 = 0x6000;       // 0
		TIM4->CCMR2 = 0x6060;  // 0x6060
		TIM4->CCER  = 0x1110;  // 0x1100 set capture/compare enable register
		TIM4->SMCR  = 0;       // 0 set slave mode control register
		
		TIM4->CR1 = 1u<<2;    // 1: URS: Only counter overflow/underflow
		// generates an update interrupt or DMA
		// request if enabled.

		TIM4->CR2 = 0;        // 0x0 set command register 2

		TIM4->CR1 |= 1u<<0;   // 0: enable timer
	}
}

