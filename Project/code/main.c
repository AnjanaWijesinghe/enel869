#include <stdio.h>
#include "stm32f10x.h"
#include "time.h"


void gpio_ports_enable(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN; //ports A & B & C clock enabled
	GPIOB->CRH = 0x44444443; // pin PB8 output mode at highest speed
}

int main(void)
{
	/*
  gpio_ports_enable();
	enable_timer();
	for(;;)  //main loop - read "forever", or you may use 'while(1)'
	{
		GPIOB->BSRR = GPIO_BSRR_BS8; 
		//TDelay_Micros(10000);
		TDelay_Millis(1000);
		GPIOB->BSRR = GPIO_BSRR_BR8; 
		//TDelay_Micros(10000);
		TDelay_Millis(1000);
	}
	*/
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;  // enable TIM4
	TIM4->PSC = 1;  // setting prescaler to 1
	TIM4->ARR = 35999;  // set auto-reload after 36,000 clks
	
	TIM4->PSC = 36-1;  // setting prescaler to 2
	TIM4->ARR = 40000;  // setting ARR to 57600 clks
	// This should give a pulse of length 1600 us
	
	TIM4->CR1 = 0;     // reset command register 1
  TIM4->CR2 = 0;     // reset command register 2

	//TIM4->PSC = 7199; 
	//TIM4->ARR = 9999;  // set auto-reload after 10,000 clks
			
	TIM4->CCR1  = 0;       // 0
	//TIM4->CCR2  = 5000;
	TIM4->CCR2  = 20000;       // setting to half the width of ARR
	TIM4->CCR2 = 1200;  // setting to 600us = low point?
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
	
	RCC->APB2ENR |= 1u<<3;	// bit 3: IOPBEN=1, enable GPIOB clock
	GPIOB->CRL = 
				// configure PB7 as TIM4_CH2 output
				(0xBu<<28);
	GPIOB->CRH = 
        // configure PB9 as TIM4_CH4 output
        (0xBu<<4) | // bits 7:4,  PB9,  output mode, 10MHz, alt func open drain
        // configure PB8 as TIM4_CH3 output
        (0xBu<<0);  // bits 3:0,  PB8,  output mode, 10MHz, alt func open drain
				
	
	// PB8 TIM4 CH3
	// PB9 TIM4 CH4
	// PB7 TIM4 CH2
	// Servo at either 1500 to 1900usec or 900-2100 µs
	// Therefore will run at 1600 us
	enable_timer();
	while (1) 
	{
		// change CCR1 to change the duty cycle and observe how the servo changes
		TIM4->CCR2 = 1800; //2500;  // setting to 1200us = low point?
		TDelay_Millis(5000);
		TIM4->CCR2 = 2300; //3000;  // setting to 1200us = med point?
		TDelay_Millis(5000);
		TIM4->CCR2 = 2600; //3300;  // setting to 1200us = high point?
		TDelay_Millis(5000);
		TIM4->CCR2 = 2500; //3200;  // setting to 1200us = med point?
		TDelay_Millis(5000);
		TIM4->CCR2 = 2450; //3150;  // setting to 1200us = med point?
		TDelay_Millis(5000);
		TIM4->CCR2 = 2300; //3000;  // setting to 1200us = med point?
		TDelay_Millis(5000);
		TIM4->CCR2 = 2200; //3000;  // setting to 1200us = med point?
		TDelay_Millis(5000);
	}   
}