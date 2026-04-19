#include "isr.h"
#include "vga.h"
#include "timer.h"

void isr_handler(registers_t* regs) {
	// (void)(regs); // suppress unused arguments

	if(regs->int_no == 32) {
		timer_tick();
	} else {
		vga_write("ISR: EXCEPTION TRIGGERED\n");

		while(1) {
			__asm__ volatile ("hlt");
		}
	}

}
