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
int read_adc = 0;


void ADC1_2_IRQHandler() 
{
	adc_val = ADC1->DR;
	//while( !( USART2->SR & USART_SR_TXE ) ) {};
	//USART2->DR = adc_val;
	
	// clear interrupt flag
	ADC1->SR &= ~(1<<1);
	
	ADC1->CR2 |= ADC_CR2_SWSTART;
}



int main(void)
{
	// enable timer 1 with 72 prescaler
	enable_timer(1, 72, 0);
	// enable timer 4 with 36 prescaler
	enable_timer(4, 36, 40000);
	//enable_timer(4, 7199, 9999);
	
	//setup_servo_timer(1800);
	setup_led_timer(0, 50, 5000);
	
	// setting default servo values
	int servo_max = 2600;
	int servo_min = 1900;
	int servo_val = 2300;
	
	enable_gpiob();
	// enable servo
	enable_gpiob_pin(7, 3, 2);
	// set servo
	set_servo_val(servo_val, servo_max, servo_min);
	
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
	
	char rxb;
	char version[] = "|| version = 0.0.2 ||";
	char read_str[100] = {0};
	
	while (1) 
	{
		print_header(version);
		print_values(servo_val, servo_max, servo_min, adc_val);
		
		//print_ir_only(adc_val);
		// read the highest level options
		/*
		// Debug the ball height to measure the IR value
		write_str_usart2("Height in cm: ");
		read_int(read_str);
		write_ch_usart2('\n');
		write_ch_usart2('\r');
		for (int counter=0; counter < 50; counter++)
		{
			print_ir_only(adc_val);
			TDelay_Millis(50);
			TDelay_Micros(67);
		}
		write_ch_usart2('\n');
		write_ch_usart2('\r');
		*/
		rxb = read_ch_usart2();
		switch(rxb)
		{
			case 114:
				//write_str_usart2("refresh");
				// r entered
				// refresh window
				break;
			case 105:
				write_str_usart2("increase 1");
				// i entered
				// increase servo by 1
				servo_val = increase_servo_val(1, servo_val, servo_max, servo_min);
				break;
			case 73:
				write_str_usart2("increase 10");
				// I entered
				// increase servo by 10
				servo_val = increase_servo_val(10, servo_val, servo_max, servo_min);
				break;
			case 100:
				write_str_usart2("decrease 1");
				// d entered
				// decrease servo by 1
				servo_val = decrease_servo_val(1, servo_val, servo_max, servo_min);
				break;
			case 68:
				write_str_usart2("decrease 10");
				// D entered
				// decrease servo by 10
				servo_val = decrease_servo_val(10, servo_val, servo_max, servo_min);
				break;
			case 104:
				write_str_usart2("Set servo high bound: ");
				// h entered
				// set servo high point
				servo_max = read_int(read_str);
				break;
			case 108:
				write_str_usart2("Set servo low bound: ");
				// l entered
				// set servo low point
				servo_min = read_int(read_str);
				break;
			case 115:
				write_str_usart2("Set servo value: ");
				// s entered
				// set servo value
				servo_val = custom_servo_val(read_int(read_str), servo_val, servo_max, servo_min);
				break;
			//case 97:
				// read adc value
				//ADC1->CR2 |= ADC_CR2_SWSTART;
				//adc_val = ADC1->DR;
				//break;
		}
		
	}   
}