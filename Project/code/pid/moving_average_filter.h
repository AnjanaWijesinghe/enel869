/** @file */
#ifndef MOVING_AVERAGE_FILTER_
#define MOVING_AVERAGE_FILTER_

#define MOVING_AVERAGE_LENGTH 5
//! Moving average filter
//! This keeps a buffer of lenght 5 [MOVING_AVERAGE_FILTER] and then applies typr of filter required to get an average from them
//! \param buffer buffer containing the values 
//! \param counter keep track of the location of the last value added
//! \param out average of the buffer
//! \param sum sum of the buffer
struct mov_avg_filter
{
	int buffer[MOVING_AVERAGE_LENGTH];
	int counter;
	int out;
	int sum;
};

//! Resets moving filter.
//! \param filter filter
void reset_average_filter(struct mov_avg_filter* instance);
//! Apply mean average filter
//! \param filter filter
//! \param input Input
//! \param *out Filtered output
void apply_average_filter(struct mov_avg_filter* instance, int input, int *out);
//! Apply median average filter
//! \param filter filter
//! \param input Input
//! \param *out Filtered output
void apply_median_filter(struct mov_avg_filter* instance, int input, int *out);

#endif /* MOVING_AVERAGE_FILTER_ */