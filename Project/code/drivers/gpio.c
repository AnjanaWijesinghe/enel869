#include "stm32f10x.h"


void enable_gpiob(void)
{
	RCC->APB2ENR |= 1u<<3;	// bit 3: IOPBEN=1, enable GPIOB clock
  //RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN; //ports A & B & C clock enabled
	//GPIOB->CRH = 0x44444443; // pin PB8 output mode at highest speed
	
}

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
void _enable_gpiob_pin_crl(int pin, int mode, int cnf)
{
	// set crl pin
	pin *= 4;
	//GPIOB->CRL |= (0xBu<<28);
	GPIOB->CRL |= (mode<<pin);
	pin += 2;
	GPIOB->CRL |= (cnf<<pin);
}

void _enable_gpiob_pin_crh(int pin, int mode, int cnf)
{
	// set crl pin
	pin *= 4;
	//GPIOB->CRL |= (0xBu<<28);
	GPIOB->CRH |= (mode<<pin);
	pin += 2;
	GPIOB->CRH |= (cnf<<pin);
}

void enable_gpiob_pin(int pin, int mode, int cnf)
{
	if(pin <= 7)
	{
		// use CRL
		_enable_gpiob_pin_crl(pin, mode, cnf);
	}
	else
	{
		// use CRH
		pin -= 8;
		_enable_gpiob_pin_crh(pin, mode, cnf);
	}
}

void enable_gpioc()
{
	RCC->APB2ENR |= 1<<4;
}

void _enable_gpioc_pin_crl(int pin, int mode, int cnf)
{
	// set crl pin
	pin *= 4;
	//GPIOB->CRL |= (0xBu<<28);
	GPIOC->CRL |= (mode<<pin);
	pin += 2;
	GPIOC->CRL |= (cnf<<pin);
}

void _enable_gpioc_pin_crh(int pin, int mode, int cnf)
{
	// set crl pin
	pin *= 4;
	//GPIOB->CRL |= (0xBu<<28);
	GPIOC->CRH |= (mode<<pin);
	pin += 2;
	GPIOC->CRH |= (cnf<<pin);
}

void enable_gpioc_pin(int pin, int mode, int cnf)
{
	if(pin <= 7)
	{
		// use CRL
		_enable_gpioc_pin_crl(pin, mode, cnf);
	}
	else
	{
		// use CRH
		pin -= 8;
		_enable_gpioc_pin_crh(pin, mode, cnf);
	}
}