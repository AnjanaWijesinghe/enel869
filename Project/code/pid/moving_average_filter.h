/** @file */
#ifndef MOVING_AVERAGE_FILTER_
#define MOVING_AVERAGE_FILTER_

#define MOVING_AVERAGE_LENGTH 5
//! Moving average filter
struct mov_avg_filter
{
	int buffer[MOVING_AVERAGE_LENGTH];
	int counter;
	int out;
	int sum;
};

//! Resets filter.
//! \param filter filter
void reset_average_filter(struct mov_avg_filter* instance);
//! Apply filter
//! \param filter filter
//! \param input Input
//! \param *out Filtered output
void apply_average_filter(struct mov_avg_filter* instance, int input, int *out);

#endif /* MOVING_AVERAGE_FILTER_ */