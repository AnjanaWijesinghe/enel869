#include "pid.h"

#define INTEGRAL_GAIN_MAX 1000
#define PID_MAX 8000

void set_pid_gain(struct PID_Param_t *par, float p, float i, float d)
{
	par->Kp = p;
	par->Ki = i;
	par->Kd = d;
	
	par->last_error = 0;
	par->last_last_error = 0;
	par->error_integral = 0;
	par->output = 0;
	
	par->Ts = 0;
	
	par->output_mapped = 0;
}

void reset_pid(struct PID_Param_t *par)
{	
	par->last_error = 0;
	par->last_last_error = 0;
	par->error_integral = 0;
	par->output = 0;
	
	par->Ts = 0;
	
	par->output_mapped = 0;
}

int simple_step_calculation(int curr_val, int input_error, int step_len)
{
	if (input_error > step_len)
	{
		curr_val += 5;
	}
	else if (input_error < -step_len)
	{
		curr_val -= 5;
	}
	return curr_val;
}

void PID_Calculation(struct PID_Param_t *par, int input_error, int sampling_rate)
{
	/*
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
	*/
	float PID_p, PID_i, PID_d;
	float input_error_f = (float)input_error;
	float sampling_rate_f = (float)sampling_rate / 1000; // converting milli seconds to seconds
	
	PID_p = par->Kp * input_error_f;
	PID_i = par->error_integral + (input_error_f * sampling_rate_f);
	par->error_integral = PID_i;
	if (par->error_integral > INTEGRAL_GAIN_MAX)
	{
		par->error_integral = INTEGRAL_GAIN_MAX;
	}
	if (par->error_integral < -INTEGRAL_GAIN_MAX)
	{
		par->error_integral = -INTEGRAL_GAIN_MAX;
	}
	PID_i = par->Ki * PID_i;
	
	PID_d = par->Kd * ((input_error_f - par->last_error) / sampling_rate_f);  // ) * (- (2 * ) + par->last_last_error);
	
	par->output = PID_p + PID_i + PID_d;
	
	par->last_last_error = par->last_error;
	par->last_error = input_error_f;
}

void PID_Calculation_b(struct PID_Param_t *par, int input_error, int sampling_rate)
{
	int PID_p, PID_i, PID_d, PID_total;
	
	PID_p = par->Kp * input_error;
	//int dist_difference = input_error - par->last_error;
	PID_d = par->Kd * ((input_error - par->last_error) * sampling_rate);
	
	if (-3 < input_error && input_error < 3)
	{
		//PID_i = PID_i + (par->Ki * input_error);
		PID_i = 0;
	}
	else
	{
		PID_i = 0;
	}
	PID_total = PID_p + PID_i + PID_d;
	par->output = PID_total;
	par->last_error = input_error;
}

void PID_Calculation_c(struct PID_Param_t *par, int input_error, int sampling_rate)
{
	float PID_p, PID_i, PID_d;
	float input_error_f = (float)input_error;
	float sampling_rate_f = (float)sampling_rate / 1000; // converting milli seconds to seconds
	
	PID_p = par->Kp * (input_error_f - par->last_error);
	PID_i = par->Ki * input_error_f * sampling_rate_f;
	PID_d = (par->Kd / sampling_rate_f) * (input_error_f - (2 * par->last_error) + par->last_last_error);
	
	par->output = PID_p + PID_i + PID_d;
	
	par->last_last_error = par->last_error;
	par->last_error = input_error_f;
}

void PID_map(struct PID_Param_t *par, int max_v, int min_v, int servo_max, int servo_min)
{
	/*
	float max_v_f = (float)max_v;
	float min_v_f = (float)min_v;
	float servo_max_f = (float)servo_max;
	float servo_min_f = (float)servo_min;
	
	float out = (float)par->output;
	if (out > max_v_f)
	{
		out = max_v_f;
	}
	else if (out < min_v_f)
	{
		out = min_v_f;
	}

	out = (out - min_v_f) / (max_v_f - min_v_f);
	out = (out * (servo_max_f - servo_min_f)) + servo_min_f;
	par->output_mapped = (int)out;
	*/
	//par->output_mapped = (((par->output - ir_min)/(ir_max - ir_min)) *
	//	(servo_max - servo_min)) + servo_min;
	//int new_servo_val = par->output + servo_val;
	if (par->output >= max_v)
	{
		par->output_mapped = max_v;
	}
	else if (par->output <= min_v)
	{
		par->output_mapped = min_v;
	}
	else
	{
		par->output_mapped = par->output;
	}
}