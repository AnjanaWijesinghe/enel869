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
	}
}

