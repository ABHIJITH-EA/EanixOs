#ifndef TIMER_H
#define  TIMER_H

#include <stdint.h>

void timer_tick(void);
uint32_t timer_get_ticks(void);
void timer_sleep(uint32_t ticks);

#endif
