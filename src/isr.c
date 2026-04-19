#include "vga.h"

void isr_handler() {
	vga_write("ISR HIT!!!\n");

	while(1) {
		__asm__ volatile ("hlt");
	}
}
