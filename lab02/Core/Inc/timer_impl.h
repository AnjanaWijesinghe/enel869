#ifndef TIMER_IMPL_H
#define TIMER_IMPL_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "timer.h"

void timer_init(void);
uint16_t timer_start(void);
uint16_t timer_stop(uint16_t start_time);
void timer_shutdown(void);

#endif
