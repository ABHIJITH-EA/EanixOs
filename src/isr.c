#include "isr.h"
#include "vga.h"

void isr_handler(registers_t* regs) {

	(void)(regs); // suppress unused arguments

	vga_write("ISR: EXCEPTION TRIGGERED\n");

	while(1) {
		__asm__ volatile ("hlt");
	}
}
