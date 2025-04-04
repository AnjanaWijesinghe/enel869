#ifndef PID_H_
#define PID_H_

struct PID_Param_t
{
	int Kp;
	int Ki;
	int Kd;
	
	int last_error;
	int error_integral;
	int output;
	
	float Ts;
	
	int output_mapped;
};

	
void set_pid_gain(struct PID_Param_t *par, int p, int i, int d);
void reset_pid(struct PID_Param_t *par);
void PID_Calculation(struct PID_Param_t *par, int input_error, int sampling_rate);
void PID_Calculation_b(struct PID_Param_t *par, int input_error, int sampling_rate);
void PID_map(struct PID_Param_t *par, int servo_max, int servo_min, int ir_max, int ir_min);

#endif /* PID_H_ */