void enable_usart2();
void write_ch_usart2(int ch);
char read_ch_usart2();
void write_str_usart2(char write_str[]);
void read_str_usart2(char read_str[]);
void print_header(char version[]);
void write_string(char write_str[]);
int read_int(char read_str[]);
void print_values(int curr_servo, int max_servo, int min_servo, int curr_ir);