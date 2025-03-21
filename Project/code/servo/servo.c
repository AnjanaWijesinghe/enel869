#include "stm32f10x.h"


void setup_servo_timer(int ccr2)
{
	// add assertion to check if arr is in range
	
	//TIM4->ARR = arr;  // setting ARR to 40000 clks
	//TIM4->CCR2  = arr/2;       // setting to half the width of ARR
	// This should give a pulse of length 20ms
	
	TIM4->CR1 = 0;     // reset command register 1
  TIM4->CR2 = 0;     // reset command register 2
	
	TIM4->CCR2 = ccr2;  // setting to 600us = low point?
	
	
	TIM4->CCMR1 = 0x6000;       // 0
	
	TIM4->CCER  = 0x1110;  // 0x1100 set capture/compare enable register
	TIM4->SMCR  = 0;       // 0 set slave mode control register
			
	TIM4->CR1 = 1u<<2;    // 1: URS: Only counter overflow/underflow
		 // generates an update interrupt or DMA
		 // request if enabled.

	TIM4->CR2 = 0;        // 0x0 set command register 2

	TIM4->CR1 |= 1u<<0;   // 0: enable timer
}