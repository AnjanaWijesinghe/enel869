#include "../cli/cli.h"
#include "../timer/time.h"

void test_ir_values()
{
	// NOTE: this doesn't work as is
	//char read_str[100] = {0};
	int adc_val = 0;
	
	// Debug the ball height to measure the IR value
	write_str_usart2("Height in cm: ");
	//read_int(read_str);
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
}