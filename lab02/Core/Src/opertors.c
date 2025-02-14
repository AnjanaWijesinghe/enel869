#include "operators.h"
#include "timer_impl.h"

#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"


uint8_t gen_rand_8(void)
{
	uint8_t x;
	x = rand() & 0xff;

	return x;
}


uint32_t gen_rand_32(void)
{
	uint32_t x;
	x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;

	return x;
}

uint64_t gen_rand_64(void)
{
	uint64_t x;
	x = gen_rand_32();
	x |= gen_rand_32() << 32;

	return x;
}

// Addition functions
uint16_t time_to_add_32(void)
{
	volatile uint32_t testValue1 = 0;
	volatile uint32_t testValue2 = 0;
	volatile uint32_t testValue3 = 0;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		testValue1 = gen_rand_32();
		testValue2 = gen_rand_32();

		timer_init();
		CounterTicks = timer_start();
		testValue3 = testValue2 + testValue1;
		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

uint16_t time_to_add_64(void)
{
	volatile uint64_t testValue1 = 0;
	volatile uint64_t testValue2 = 0;
	volatile uint64_t testValue3 = 0;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		testValue1 = gen_rand_64();
		testValue2 = gen_rand_64();

		timer_init();
		CounterTicks = timer_start();
		testValue3 = testValue2 + testValue1;
		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

// Multiplication functions
uint16_t time_to_mul_32(void)
{
	volatile uint32_t testValue1 = 0;
	volatile uint32_t testValue2 = 0;
	volatile uint32_t testValue3 = 0;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		testValue1 = gen_rand_32();
		testValue2 = gen_rand_32();

		timer_init();
		CounterTicks = timer_start();
		testValue3 = testValue2 * testValue1;
		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

uint16_t time_to_mul_64(void)
{
	volatile uint64_t testValue1 = 0;
	volatile uint64_t testValue2 = 0;
	volatile uint64_t testValue3 = 0;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		testValue1 = gen_rand_64();
		testValue2 = gen_rand_64();

		timer_init();
		CounterTicks = timer_start();
		testValue3 = testValue2 * testValue1;
		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

// Division functions
uint16_t time_to_div_32(void)
{
	volatile uint32_t testValue1 = 0;
	volatile uint32_t testValue2 = 0;
	volatile uint32_t testValue3 = 0;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		testValue1 = gen_rand_32();
		testValue2 = gen_rand_32();

		timer_init();
		CounterTicks = timer_start();
		if(testValue1 == 0)
		{
			testValue3 = 0;
		}
		else
		{
			testValue3 = testValue2 / testValue1;
		}
		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

uint16_t time_to_div_64(void)
{
	volatile uint64_t testValue1 = 0;
	volatile uint64_t testValue2 = 0;
	volatile uint64_t testValue3 = 0;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		testValue1 = gen_rand_64();
		testValue2 = gen_rand_64();

		timer_init();
		CounterTicks = timer_start();
		if(testValue1 == 0)
		{
			testValue3 = 0;
		}
		else
		{
			testValue3 = testValue2 / testValue1;
		}
		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

// structs
struct B8
{
	uint8_t x[8];
};

struct B128
{
	uint8_t x[128];
};

struct B1024
{
	uint8_t x[1024];
};

uint16_t time_to_copy_8B(void)
{
	volatile struct B8 b8;
	volatile struct B8 b8Copy;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		for(int i = 0; i < 8; i++)
		{
			b8.x[i] = gen_rand_8();
		}

		timer_init();
		CounterTicks = timer_start();

		b8Copy = b8;

		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

uint16_t time_to_copy_128B(void)
{
	volatile struct B128 b128;
	volatile struct B128 b128Copy;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		for(int i = 0; i < 128; i++)
		{
			b128.x[i] = gen_rand_8();
		}

		timer_init();
		CounterTicks = timer_start();

		b128Copy = b128;

		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}

uint16_t time_to_copy_1024B(void)
{
	volatile struct B1024 b1024;
	volatile struct B1024 b1024Copy;

	uint16_t CounterTicks = 0;
	uint16_t CounterTicks2 = 0;
	uint16_t time_sum = 0;

	for(int i = 0; i < 100; i++)
	{
		for(int i = 0; i < 1024; i++)
		{
			b1024.x[i] = gen_rand_8();
		}

		timer_init();
		CounterTicks = timer_start();

		b1024Copy = b1024;

		CounterTicks2 = timer_stop(CounterTicks);
		timer_shutdown();
		time_sum += CounterTicks2;
	}

	time_sum /= 100;

	return time_sum;
}
