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

int set_servo_val(int val, int max_val, int min_val)
{
	// set the servo to the new value if it is within the given range
	if(val >= min_val && val <= max_val)
	{
		TIM4->CCR2 = val;
		return 1;
	}
	return 0;
}

int custom_servo_val(int new_val, int curr_val, int max_val, int min_val)
{
	// set servo to custom value within bounds
	if (new_val > max_val)
	{
		new_val = max_val;
	}
	else if (new_val < min_val)
	{
		new_val = min_val;
	}
	if(set_servo_val(new_val, max_val, min_val) == 1)
	{
		return new_val;
	}
	return curr_val;
}

int increase_servo_val(int inc_val, int curr_val, int max_val, int min_val)
{
	// increase the value of the servo by the given amount
	int new_val = curr_val + inc_val;
	if (set_servo_val(new_val, max_val, min_val) == 1)
	{
		return new_val;
	}
	return curr_val;
}

int decrease_servo_val(int dec_val, int curr_val, int max_val, int min_val)
{
	// increase the value of the servo by the given amount
	int new_val = curr_val - dec_val;
	if (set_servo_val(new_val, max_val, min_val) == 1)
	{
		return new_val;
	}
	return curr_val;
}
