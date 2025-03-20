#include "stm32f10x.h"


void enable_timer(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //0x0800;  // setup timer 1 bus
	TIM1->PSC = (72-1);  //set presclar to 72 
	//TIM1->ARR = (10000-1);  //set auto reload to 10,000
	//TIM1->CR1 |= 1;  // enable counter
}

void TDelay_Micros(int MicroS)
{
	TIM1->CNT = 0;  // reset counter
	TIM1->ARR = MicroS - 1;  //set auto reload
	TIM1->CR1 |= 0x9;  // enable counter
	while(TIM1->CR1 & 1)
	{	}
}

void TDelay_Millis(int milliS)
{
	int i = 0;
	for(i=0; i<milliS; i++)
	{
		TDelay_Micros(1000);
	}
}