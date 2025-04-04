#include <stdio.h>

#include "stm32f10x.h"

#include "timer/time.h"
#include "drivers/gpio.h"
#include "drivers/clock.h"
#include "servo/servo.h"
#include "led/led.h"
#include "cli/cli.h"
#include "ir/ir.h"
#include "pid/pid.h"
#include "pid/moving_average_filter.h"


int adc_val = 0;
char global_rxb;

struct PID_Param_t pid;
struct mov_avg_filter mov_avg_instance;

char version[] = "|| version = 0.4.0 ||";

// 0 is control ball mode
// 1 is debug mode
int machine_state = 0;

// setting default servo values
int servo_max = 2600;
int servo_min = 1900;
int servo_val = 2300;

// required height in IR value
int required_height = 2600;

void ADC1_2_IRQHandler() 
{
	//adc_val = ADC1->DR;
	apply_average_filter(&mov_avg_instance, ADC1->DR, &adc_val);
	//while( !( USART2->SR & USART_SR_TXE ) ) {};
	//USART2->DR = adc_val;
	
	// clear interrupt flag
	ADC1->SR &= ~(1<<1);
	
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

void USART2_IRQHandler() 
{
	// change machine state
	machine_state = 1;
	
	global_rxb = USART2->DR;
	
	// clear interrupt
	USART2->SR &= ~(1<<5);
}

void debug_menu()
{
	print_debug_header(version);
	
	char rxb;
	// read input
	rxb = read_ch_usart2();
	switch(rxb)
	{
		case 114:
			write_str_usart2("refresh");
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
			servo_max = read_int(servo_max);
			break;
		case 108:
			write_str_usart2("Set servo low bound: ");
			// l entered
			// set servo low point
			servo_min = read_int(servo_min);
			break;
		case 115:
			write_str_usart2("Set servo value: ");
			// s entered
			// set servo value
			servo_val = custom_servo_val(read_int(servo_val), servo_val, servo_max, servo_min);
			break;
		case 49:
			write_str_usart2("Set Kp value: ");
			// s entered
			// set servo value
			pid.Kp = read_int(servo_val);
			break;
		case 50:
			write_str_usart2("Set Ki value: ");
			// s entered
			// set servo value
			pid.Ki = read_int(servo_val);
			break;
		case 51:
			write_str_usart2("Set Kd value: ");
			// s entered
			// set servo value
			pid.Kd = read_int(servo_val);
			break;
		case 97:
			write_str_usart2("Set height value in IR: ");
			// s entered
			// set servo value
			required_height = read_int(required_height);
			break;
	}
	// set the machine back into normal state
	machine_state = 0;
}


int main(void)
{
	// set defaults for pid and moving average
	set_pid_gain(&pid, 5, 5, 5);
	reset_average_filter(&mov_avg_instance);
	
	// enable timer 1 with 72 prescaler
	enable_timer(1, 72, 0);
	// enable timer 4 with 36 prescaler
	enable_timer(4, 36, 40000);
	//enable_timer(4, 7199, 9999);
	
	//setup_servo_timer(1800);
	setup_led_timer(0, 50, 5000);
	
	// setting default servo values
	//int servo_max = 2600;
	//int servo_min = 1900;
	//int servo_val = 2300;
	
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
	
	//char rxb;
	//char read_str[100] = {0};
	
	print_main_header(version);
	while (1) 
	{
		print_values(servo_val, servo_max, servo_min, adc_val, required_height, pid.Kp, pid.Ki, pid.Kd, pid.output);
		
		if(machine_state == 0)
		{
			// PID mode
			//PID_Calculation(&pid, adc_val - required_height, 1000);
			PID_Calculation_b(&pid, adc_val - required_height, 1000);
			PID_map(&pid, servo_max, servo_min, 2850, 2450);
			servo_val = custom_servo_val(pid.output_mapped, servo_val, servo_max, servo_min);
			TDelay_Millis(1);
		}
		else if (machine_state == 1)
		{
			// limbo mode
			disable_rx_interrupt();
			
			switch(global_rxb)
			{
				case 114:
					//write_str_usart2("refresh");
					// r entered
					// refresh window
					break;
				case 105:
					// i entered
					// increase servo by 1
					servo_val = increase_servo_val(1, servo_val, servo_max, servo_min);
					break;
				case 73:
					// I entered
					// increase servo by 10
					servo_val = increase_servo_val(10, servo_val, servo_max, servo_min);
					break;
				case 100:
					// d entered
					// decrease servo by 1
					servo_val = decrease_servo_val(1, servo_val, servo_max, servo_min);
					break;
				case 68:
					// D entered
					// decrease servo by 10
					servo_val = decrease_servo_val(10, servo_val, servo_max, servo_min);
					break;
				case 113:
					debug_menu();
					break;
			}
			machine_state = 0;
			// enable rx interrupts
			enable_rx_interrupt();
		}
		else
		{
		}
	}   
}