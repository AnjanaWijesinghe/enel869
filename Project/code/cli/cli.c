#include "stm32f10x.h"


void enable_usart2()
{
	RCC->APB1ENR  |=  ( RCC_APB1ENR_USART2EN );
	RCC->APB2ENR  |=  ( RCC_APB2ENR_IOPAEN );
	GPIOA->CRL = 0x00000000;
	
	// Configure pins A2, A3 for USART2.
	// PA2 is Tx and PA3 is Rx
	GPIOA->CRL |= 0x9 << 8;
	//GPIOA->CRL |= 0x2 << 10;
	
	GPIOA->CRL |= 0x4 << 12;
	//GPIOA->CRL |= 0x1 << 14;
	/*GPIOA->CRL    &= ( GPIO_CRL_MODE2 |
										 GPIO_CRL_CNF2 |
										 GPIO_CRL_MODE3 |
										 GPIO_CRL_CNF3 );
	GPIOA->CRL    |= ( ( 0x1 << GPIO_CRL_MODE2_Pos ) |
										 ( 0x2 << GPIO_CRL_CNF2_Pos ) |
										 ( 0x0 << GPIO_CRL_MODE3_Pos ) |
										 ( 0x1 << GPIO_CRL_CNF3_Pos ) );*/
	// set baudrate
	//uint32_t baudrate = 115200;
	//uint32_t uartdiv = SystemCoreClock / baudrate;
	//USART2->BRR = ((SystemCoreClock + (baudrate / 2u)) / baudrate);
	//uint16_t uartdiv = SystemCoreClock / 115200;
	//USART2->BRR = (uartdiv % 16) << 0;
	//USART2->BRR |= (uartdiv / 16) << 4;
	//USART2->BRR = 625u;
	//USART2->BRR |= 27u<<4;
	// usartdiv = 39.0625
	// mantissa 39 -> 27 hex
	// fraction 1 -> 1 hex
	
	// USART2 is connected to APB1 which is at 36Mhz (max available for this)
	// USARTDIV = 19.53125
	// Mantissa = 13
	// Fraction = 9
	
	
	USART2->BRR = 0x138;
	
	// enable tx and rx on cr1
	USART2->CR1 |= 1u<<2;
	USART2->CR1 |= 1u<<3;
	
	// enable usart2
	USART2->CR1 |= 1u<<13;
}

void write_usart2(int ch)
{
	// check if its not empty and write
	while(!(USART2->SR & (1u<<7)))
		;
	USART2->DR = (ch & 0xFF);
}

char read_usart2()
{
	while(!(USART2->SR & (1u<<5)))
		;
	return USART2->DR;
}