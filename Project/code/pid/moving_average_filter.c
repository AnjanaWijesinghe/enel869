#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "moving_average_filter.h"

void reset_average_filter(struct mov_avg_filter* instance)
{
	instance->counter = 0;
	instance->sum = 0;
	instance->out = 0;
	for (int i=0; i<MOVING_AVERAGE_LENGTH; i++)
	{
		instance->buffer[i] = 0;
	}
}

void apply_average_filter(struct mov_avg_filter* instance, int input, int *out)
{
	instance->sum += input - instance->buffer[instance->counter];
	instance->buffer[instance->counter] = input;
	instance->counter++;
	if (instance->counter >= MOVING_AVERAGE_LENGTH)
	{
		instance->counter = 0;
	}
	instance->out = instance->sum / MOVING_AVERAGE_LENGTH;
	//normalization
	(*out) = instance->out;
}

int compare( const void* a, const void* b)
{
   int int_a = * ( (int*) a );
   int int_b = * ( (int*) b );

   // an easy expression for comparing
   return (int_a > int_b) - (int_a < int_b);
}

void apply_median_filter(struct mov_avg_filter* instance, int input, int *out)
{
	instance->buffer[instance->counter] = input;
	instance->counter++;
	if (instance->counter >= MOVING_AVERAGE_LENGTH)
	{
		instance->counter = 0;
	}
	
	int temp_buffer[MOVING_AVERAGE_LENGTH];
	memcpy(temp_buffer, instance->buffer, MOVING_AVERAGE_LENGTH * sizeof(int));
	qsort(temp_buffer, MOVING_AVERAGE_LENGTH, sizeof(int), compare );
	
	(*out) = temp_buffer[3];
}