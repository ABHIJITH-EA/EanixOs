#include "timer.h"

static volatile uint32_t tick = 0;

void timer_tick() {
	tick++;
}

uint32_t timer_get_ticks() {
	return tick;
}

void timer_sleep(uint32_t ticks) {
	uint32_t start = tick;

	while((tick - start) < ticks) {
		__asm__ volatile ("hlt");
	}

}
