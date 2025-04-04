#include "pid.h"

#define INTEGRAL_GAIN_MAX 2000000
#define PID_MAX 8000

void set_pid_gain(struct PID_Param_t *par, int p, int i, int d)
{
	par->Kp = p;
	par->Ki = i;
	par->Kd = d;
}

void reset_pid(struct PID_Param_t *par)
{
	par->Kp = 0;
	par->Ki = 0;
	par->Kd = 0;
	
	par->last_error = 0;
	par->error_integral = 0;
	par->output = 0;
	
	par->Ts = 0;
	
	par->output_mapped = 0;
}

void PID_Calculation(struct PID_Param_t *par, int input_error, int sampling_rate)
{
	par->error_integral += input_error;
	if (par->error_integral > INTEGRAL_GAIN_MAX)
	{
		par->error_integral = INTEGRAL_GAIN_MAX;
	}
	if (par->error_integral < -INTEGRAL_GAIN_MAX)
	{
		par->error_integral = -INTEGRAL_GAIN_MAX;
	}
	par->output = (par->Kp * input_error) +
		(par->Ki * (par->error_integral) / sampling_rate) +
		(par->Kd * sampling_rate * (input_error - par->last_error));
	
	if (par->output >= PID_MAX)
	{
		par->output = PID_MAX;
	}
	if (par->output <= -PID_MAX)
	{
		par->output = -PID_MAX;
	}
}

void PID_Calculation_b(struct PID_Param_t *par, int input_error, int sampling_rate)
{
	int PID_p, PID_i, PID_d, PID_total;
	
	PID_p = par->Kp * input_error;
	int dist_difference = input_error - par->last_error;
	PID_d = par->Kd * ((input_error - par->last_error) * sampling_rate);
	
	if (-3 < input_error && input_error < 3)
	{
		PID_i = PID_i + (par->Ki * input_error);
	}
	else
	{
		PID_i = 0;
	}
	PID_total = PID_p + PID_i + PID_d;
	par->output = PID_total;
	par->last_error = input_error;
}

void PID_map(struct PID_Param_t *par, int servo_max, int servo_min, int ir_max, int ir_min)
{
	par->output_mapped = (((par->output - ir_min)/(ir_max - ir_min)) *
		(servo_max - servo_min)) + servo_min;
}