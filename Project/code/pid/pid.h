#ifndef PID_H_
#define PID_H_

struct PID_Param_t
{
	float Kp;
	float Ki;
	float Kd;
	
	float last_error;
	float last_last_error;
	float error_integral;
	float output;
	
	float Ts;
	
	int output_mapped;
};

	
void set_pid_gain(struct PID_Param_t *par, float p, float i, float d);
void reset_pid(struct PID_Param_t *par);
void PID_Calculation(struct PID_Param_t *par, int input_error, int sampling_rate);
void PID_Calculation_b(struct PID_Param_t *par, int input_error, int sampling_rate);
void PID_Calculation_c(struct PID_Param_t *par, int input_error, int sampling_rate);
void PID_map(struct PID_Param_t *par, int servo_max, int servo_min);
int simple_step_calculation(int curr_val, int input_error, int step_len);

#endif /* PID_H_ */