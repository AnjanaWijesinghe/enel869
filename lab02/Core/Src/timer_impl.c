#include "timer_impl.h"


void timer_init(void)
{
	RCC->APB1ENR |= 0x00000002;
	TIM3->CR1 = 0x0001;
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
