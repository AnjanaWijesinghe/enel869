#include "timer_impl.h"


void timer_init(void)
{
	RCC->APB1ENR |= 0x00000002;
	TIM3->CR1 = 0x0001;

	// setting up external clock
//	TIM3->SMCR |= TIM_SMCR_ETP;
//	TIM3->SMCR |= TIM_SMCR_ETF;
//	TIM3->SMCR |= TIM_SMCR_ECE;
////	TIM3->SMCR = 0x4F07;
//	TIM3->CCMR1 |= TIM_CCMR1_OC2M;
//	TIM3->CCER |= TIM_CCER_CC2E;
//	TIM3->CCR2 = 0x02;
//	TIM3->CR1 |= TIM_CR1_CEN;
}

uint16_t timer_start(void)
{
	return TIM3->CNT;
}

uint16_t timer_stop(uint16_t start_time)
{
	return (TIM3->CNT - start_time);
}

void timer_shutdown(void)
{
	TIM3->CNT = 0x0000;
	TIM3->CR1 = 0x0000;
	RCC->APB1ENR &= 0xfffffffd;
}
