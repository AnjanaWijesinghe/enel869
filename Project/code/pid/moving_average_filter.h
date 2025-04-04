#ifndef MOVING_AVERAGE_FILTER_
#define MOVING_AVERAGE_FILTER_

#define MOVING_AVERAGE_LENGTH 5
struct mov_avg_filter
{
	int buffer[MOVING_AVERAGE_LENGTH];
	int counter;
	int out;
	int sum;
};

void reset_average_filter(struct mov_avg_filter* instance);
void apply_average_filter(struct mov_avg_filter* instance, int input, int *out);

#endif /* MOVING_AVERAGE_FILTER_ */