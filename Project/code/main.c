#include <stdio.h>

#include "stm32f10x.h"

#include "timer/time.h"
#include "drivers/gpio.h"
#include "drivers/clock.h"
#include "servo/servo.h"
#include "led/led.h"
#include "cli/cli.h"
#include "ir/ir.h"


int adc_val = 0;


void ADC1_2_IRQHandler() 
{
	adc_val = ADC1->DR;
	//while( !( USART2->SR & USART_SR_TXE ) ) {};
	//USART2->DR = adc_val;
	
	// clear interrupt flag
	ADC1->SR &= ~(1<<1);
	
	//ADC1->CR2 |= ADC_CR2_SWSTART;
}



int main(void)
{
	// enable timer 1 with 72 prescaler
	enable_timer(1, 72, 0);
	// enable timer 4 with 36 prescaler
	//enable_timer(4, 36, 40000);
	enable_timer(4, 7199, 9999);
	
	//setup_servo_timer(1800);
	setup_led_timer(0, 50, 5000);
	
	enable_gpiob();
	// enable servo
	enable_gpiob_pin(7, 3, 2);
	// enable led pa9
	enable_gpiob_pin(9, 3, 2);
	// enable led pa8
	enable_gpiob_pin(8, 3, 2);
	
	enable_gpioc();
	// enable ir
	enable_gpioc_pin(0, 0, 1);
	enable_ir();
	
	enable_usart2();
	start_ir_adc();
	char rxb = 'a';
	rxb = 'a';
	while (1) 
	{
		rxb = adc_val;
		while( !( USART2->SR & USART_SR_RXNE ) ) {};
    rxb = USART2->DR;
		
		//rxb = 'a';
		//while( !( USART2->SR & USART_SR_TXE ) ) {};
		//USART2->DR = rxb;
		
		/*while( !( USART2->SR & USART_SR_RXNE ) ) 
		{
		}
		rxb = USART2->DR;
		while( !( USART2->SR & USART_SR_TXE ) )
		{
		}
		USART2->DR = rxb;*/
		/*rxb = 'a';
		USART2->DR = rxb;
		while( !( USART2->SR & USART_SR_TXE ) )
		{
		}
		USART2->DR = rxb;
		rxb = 'a';*/
		// change CCR1 to change the duty cycle and observe how the servo changes
		/*TIM4->CCR2 = 1800; //2500;  // setting to 1200us = low point?
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
		TDelay_Millis(5000);*/
	}   
}