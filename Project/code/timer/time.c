#include "stm32f10x.h"


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