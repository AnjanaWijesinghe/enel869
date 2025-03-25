#include "stm32f10x.h"

void enable_ir()
{
	// enabling ADC1 clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	// setting channel 10 to 55.5 cycles
	ADC1->SMPR1 |= 5u<<0; // 101 at bit 0
	// enable scan mode
	ADC1->CR1 |= ADC_CR1_SCAN;
	// enable interrupt for eoc
	ADC1->CR1 |= ADC_CR1_EOCIE;
	// enable swstart
	ADC1->CR2 |= 7u<<17; // 111 at bit 17
	// enable adc
	ADC1->CR2 |= ADC_CR2_ADON;
	// setting external trigger
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	// initialize reset calibration
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while(ADC1->CR1 & ADC_CR2_RSTCAL)
	{
		// wait for initialization to complete
	}
	// initialize adc calibration
	ADC1->CR2 |= ADC_CR2_CAL;
	while(ADC1->CR2 & ADC_CR2_CAL)
	{
		// wait for calibration
	}
	// set interrupt
	NVIC->ISER[0] |= NVIC_ISER_SETENA_18;
}

void start_ir_adc()
{
	// enable swstart
	ADC1->CR2 |= ADC_CR2_SWSTART;
}