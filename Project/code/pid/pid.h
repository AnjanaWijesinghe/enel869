/** @file */
#ifndef PID_H_
#define PID_H_

//! PID parameters
//! \param Kp P constant
//! \param Ki I constant
//! \param Kd D constant
//! \param last_error the previous input error
//! \param las_last_error the input error before the previous input error
//! \param error_integral the last integral error
//! \param output the PID output
//! \param Ts the sampling time
//! \param output_mapped the output limited to the range (max PID change per iteration range)
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

//! Set PID values
//! \param PID 
//! \param p P value
//! \param i I value
//! \param d D value
void set_pid_gain(struct PID_Param_t *par, float p, float i, float d);

//! Reset PID values (does not affect p, i, and d constants).
void reset_pid(struct PID_Param_t *par);

//! PID Caculation method A
//! \param PID pid
//! \param input_error Input error
//! \param sampling_rate Sampling rate
void PID_Calculation(struct PID_Param_t *par, int input_error, int sampling_rate);

//! PID Calculation method B
//! \param PID pid
//! \param input_error Input error
//! \param sampling_rate Sampling rate
void PID_Calculation_b(struct PID_Param_t *par, int input_error, int sampling_rate);

//! PID Calculation method C
//! \param PID pid
//! \param input_error Input error
//! \param sampling_rate Sampling rate
void PID_Calculation_c(struct PID_Param_t *par, int input_error, int sampling_rate);

//! PID map.
//! Limits the output to the given range.
//! \param PID pid
//! \param servo_max Max value to increase by
//! \param servo_min Max value to decrease by
void PID_map(struct PID_Param_t *par, int max_v, int min_v, int servo_max, int servo_min);

//! Simple on/off controller.
//! \param curr_val Current value
//! \param input_error Input error
//! \param step_len the error to change
int simple_step_calculation(int curr_val, int input_error, int step_len);

#endif /* PID_H_ */