#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f1xx_hal.h"

uint8_t gen_rand_8(void);
uint32_t gen_rand_32(void);
uint64_t gen_rand_64(void);

uint16_t time_to_add_32(void);
uint16_t time_to_add_64(void);

uint16_t time_to_mul_32(void);
uint16_t time_to_mul_64(void);

uint16_t time_to_div_32(void);
uint16_t time_to_div_64(void);

uint16_t time_to_copy_8B(void);
uint16_t time_to_copy_128B(void);
uint16_t time_to_copy_1024B(void);
