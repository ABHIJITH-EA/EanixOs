#include "isr.h"
#include "vga.h"
#include "timer.h"
#include "io.h"

char scancode_table[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',
};

void isr_handler(registers_t* regs) {
	// (void)(regs); // suppress unused arguments

	if(regs->int_no == 32) {
		timer_tick();
	} else if(regs->int_no == 33) {
		uint8_t scancode = inb(0x60);
		if(scancode < 128) {
			char c = scancode_table[scancode];
			if(c) {
				vga_put_char(c);
			}
		}

	} else {
		vga_write("ISR: EXCEPTION TRIGGERED\n");

		while(1) {
			__asm__ volatile ("hlt");
		}
	}

}
