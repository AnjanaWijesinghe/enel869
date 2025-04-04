#include "stm32f10x.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.h"

/*char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}*/

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
	
	enable_rx_interrupt();
	
	// enable tx and rx on cr1
	USART2->CR1 |= 1u<<2;
	USART2->CR1 |= 1u<<3;
	
	// enable usart2
	USART2->CR1 |= 1u<<13;
	
	// enable interrupt in nvic
	NVIC->ISER[1] |= NVIC_ISER_SETENA_6;
}

void enable_rx_interrupt()
{
	// enable interrupt RXNEIE
	USART2->CR1 |= 1u<<5;
}

void disable_rx_interrupt()
{
	// disable interrupt RXNEIE
	USART2->CR1 &= ~(1<<5);
}

void write_ch_usart2(int ch)
{
	// check if its not empty and write char to usart
	while( !( USART2->SR & USART_SR_TXE ) ) {};
	USART2->DR = ch;
}

void write_str_usart2(char write_str[])
{
	int i = 0;
	while(write_str[i])
	{
		if (write_str[i] == 13)
		{
			// if enter, break
			break;
		}
		write_ch_usart2(write_str[i]);
		i++;
	}
	//write_ch_usart2('\n');
}

void write_string(char write_str[])
{
	write_str_usart2(write_str);
	write_ch_usart2('\n');
	write_ch_usart2('\r');
}
	

char read_ch_usart2()
{
	// read char from usart
	while( !( USART2->SR & USART_SR_RXNE ) ) {};
	char rxb = USART2->DR;
	return rxb;
}

void read_str_usart2(char read_str[])
{
	// read until an enter
	char rxb;
	//char read_str[100] = {0};
	int i = 0;
	do
	{
		rxb = read_ch_usart2();
		write_ch_usart2(rxb);
		read_str[i] = rxb;
		i++;
	} while(rxb != 13);
}

int read_int(int curr_val)
{
	// read an integer value from cli
	char read_str[100] = {0};
	read_str_usart2(read_str);

	int num = 0;
	int i = 0;
	while (read_str[i] && (read_str[i] >= '0' && read_str[i] <= '9')){
			num = num * 10 + (read_str[i] - '0');
			i++;
	}
	if(num == 0)
	{
		return curr_val;
	}
	return num;
}

void print_debug_header(char version[])
{
	// print out the version
	write_ch_usart2('\n');
	write_ch_usart2('\n');
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("||----||");
	write_str_usart2(version);
	write_str_usart2("||----||");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	
	write_str_usart2("Usage:");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("r - exit");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("i - increase servo by 1");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("I - increase servo by 10");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("d - decrease servo by 1");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("D - decrease servo by 10");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("s - set servo value");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("h - set servo high limit");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("l - set servo low limit");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("a - set height value in IR");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("#1 - set Kp");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("#2 - set Ki");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("#3 - set Kd");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
}

void print_main_header(char version[])
{
	// print out the version
	write_ch_usart2('\n');
	write_ch_usart2('\n');
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("||----||");
	write_str_usart2(version);
	write_str_usart2("||----||");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	
	write_str_usart2("Usage:");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("i - increase servo by 1");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("I - increase servo by 10");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("d - decrease servo by 1");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("D - decrease servo by 10");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("q - enter debug mode");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
}

void print_values(int curr_servo, int max_servo, int min_servo, int curr_ir, int req_ir, int kp, int ki, int kd, int pid)
{
	// print the running values

	char curr_servo_str[5];
	char max_servo_str[5];
	char min_servo_str[5];
	char curr_ir_str[5];
	char req_ir_str[5];
	char kp_str[5];
	char ki_str[5];
	char kd_str[5];
	char pid_str[5];
	
	sprintf(curr_servo_str,"%d",curr_servo);
	sprintf(max_servo_str,"%d",max_servo);
	sprintf(min_servo_str,"%d",min_servo);
	sprintf(curr_ir_str,"%d",curr_ir);
	sprintf(req_ir_str,"%d",req_ir);
	sprintf(kp_str,"%d",kp);
	sprintf(ki_str,"%d",ki);
	sprintf(kd_str,"%d",kd);
	sprintf(pid_str,"%d",pid);
	
	//write_ch_usart2('\n');
	write_str_usart2("Servo Max: ");
	write_str_usart2(max_servo_str);
	write_str_usart2(" | Servo Min: ");
	write_str_usart2(min_servo_str);
	//write_ch_usart2('\n');
	//write_ch_usart2('\r');
	write_str_usart2(" | Servo val: ");
	write_str_usart2(curr_servo_str);
	write_str_usart2(" | IR val: ");
	write_str_usart2(curr_ir_str);
	write_str_usart2(" | Req IR val: ");
	write_str_usart2(req_ir_str);
	write_str_usart2(" | Kp: ");
	write_str_usart2(kp_str);
	write_str_usart2(" | Ki: ");
	write_str_usart2(ki_str);
	write_str_usart2(" | Kd: ");
	write_str_usart2(kd_str);
	write_str_usart2(" | PID: ");
	write_str_usart2(pid_str);
	write_str_usart2("                    ");
	//write_ch_usart2('\n');
	write_ch_usart2('\r');
}

void print_ir_only(int curr_ir)
{
	char curr_ir_str[5];
	sprintf(curr_ir_str,"%d",curr_ir);
	
	write_str_usart2(curr_ir_str);
	write_ch_usart2('\n');
	write_ch_usart2('\r');
}