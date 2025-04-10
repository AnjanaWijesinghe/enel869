/** @file */

//! Enable USART2
void enable_usart2();
//! Write a char to USART2.
//! \param ch char value to write
void write_ch_usart2(int ch);
//! Read a char from USART2.
//! Returns a char.
char read_ch_usart2();
//! Write string to USART2.
//! \param write_str String to write
void write_str_usart2(char write_str[]);
//! Read string from USART2.
//! \param read_str string to write read values
void read_str_usart2(char read_str[]);

//! Print main header.
//! Prints the essentials to the serial output.
//! \param version Version of the software
void print_main_header(char version[]);
//! Print debug header.
//! Prints all the debug controls from the debug menu.
//! \param version Version of the software
void print_debug_header(char version[]);
//! Write string.
//! Writes a string to the serial output and then a enter and then a refresh line.
//! \param write_str String to print
void write_string(char write_str[]);
//! Reads an int
int read_int();
//! Reads a float
float read_float();
//! Print values about the state of the machine
void print_values(
	int machine_state, 
	int curr_servo, int max_servo, int min_servo, 
	int req_ir, int curr_ir, 
	float kp, float ki, float kd, 
	int pid, int pid_mapped
);
//! Print IR values only.
//! Used for debugging.
void print_ir_only(int curr_ir);
//! Enable interrupts from a key press.
void enable_rx_interrupt();
//! Disables interrupts from a key press
void disable_rx_interrupt();