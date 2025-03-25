void setup_servo_timer(int ccr2);
int set_servo_val(int val, int max_val, int min_val);
int increase_servo_val(int inc_val, int curr_val, int max_val, int min_val);
int decrease_servo_val(int dec_val, int curr_val, int max_val, int min_val);
int custom_servo_val(int new_val, int curr_val, int max_val, int min_val);