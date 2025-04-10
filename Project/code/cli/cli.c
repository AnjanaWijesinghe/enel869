// CLI controller scripts
// Add the communication between the host and the remote are
// handled here. 
// USART2 is enabled for communication

#include "stm32f10x.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.h"

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

int read_int()
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
	//if(num == 0)
	//{
	//	return curr_val;
	//}
	return num;
}

float read_float()
{
	// read an integer value from cli and convert to float
	char read_str[100] = {0};
	read_str_usart2(read_str);

	int num = 0;
	int i = 0;
	while (read_str[i] && (read_str[i] >= '0' && read_str[i] <= '9')){
			num = num * 10 + (read_str[i] - '0');
			i++;
	}
	return (float)num/1000;
}

void print_debug_header(char version[])
{
	// print out the version
	write_ch_usart2('\n');
	write_ch_usart2('\n');
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("||----|| version: ");
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
	write_str_usart2("#1 - set Kp (/1000)");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("#2 - set Ki (/1000)");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("#3 - set Kd (/1000)");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
	write_str_usart2("To enter PID mode, press e after exiting debug menu");
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
	write_str_usart2("e - enter PID mode");
	write_ch_usart2('\n');
	write_ch_usart2('\r');
}

void print_values(int machine_state, int curr_servo, int max_servo, int min_servo, int curr_ir, int req_ir, float kp, float ki, float kd, int pid, int pid_mapped)
{
	// print the running values

	char machine_state_str[5];
	char curr_servo_str[5];
	char max_servo_str[5];
	char min_servo_str[5];
	char curr_ir_str[5];
	char req_ir_str[5];
	char kp_str[10];
	char ki_str[10];
	char kd_str[10];
	char pid_str[10];
	char pid_mapped_str[10];
	
	sprintf(machine_state_str,"%d",machine_state);
	sprintf(curr_servo_str,"%d",curr_servo);
	sprintf(max_servo_str,"%d",max_servo);
	sprintf(min_servo_str,"%d",min_servo);
	sprintf(curr_ir_str,"%d",curr_ir);
	sprintf(req_ir_str,"%d",req_ir);
	sprintf(kp_str,"%f",kp);
	sprintf(ki_str,"%f",ki);
	sprintf(kd_str,"%f",kd);
	sprintf(pid_str,"%d",pid);
	sprintf(pid_mapped_str,"%d",pid_mapped);
	
	//write_ch_usart2('\n');
	write_str_usart2("Mode: ");
	write_str_usart2(machine_state_str);
	write_str_usart2(" | Servo Max: ");
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
	write_str_usart2(" = ");
	write_str_usart2(pid_mapped_str);
	write_str_usart2(" // EOL");
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