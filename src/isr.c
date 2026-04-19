#include "isr.h"
#include "vga.h"

static int tick = 0;

void isr_handler(registers_t* regs) {
	// (void)(regs); // suppress unused arguments

	if(regs->int_no == 32) {
		tick++;
		vga_write("ISR: TICK\n");
	} else {
		vga_write("ISR: EXCEPTION TRIGGERED\n");

		while(1) {
			__asm__ volatile ("hlt");
		}
	}

}
