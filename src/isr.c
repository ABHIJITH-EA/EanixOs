#include "isr.h"
#include "timer.h"
#include "io.h"
#include "keyboard.h"
#include "terminal.h"
#include "task.h"

char scancode_table[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',
};

uint32_t* isr_handler(registers_t* regs) {
	// (void)(regs); // suppress unused arguments

	if(regs->int_no == 32) {
		timer_tick();

		task_tick();

		static int tick = 0;

		if(++tick >= 10) {
			tick = 0;
			return task_schedule((uint32_t*)regs);
		}

		return (uint32_t*)regs;
	} else if(regs->int_no == 33) {
		uint8_t scancode = inb(0x60);
		if(scancode < 128) {
			char c = scancode_table[scancode];
			if(c) {
				keyboard_push(c);
			}
		}

	} else {
		terminal_write("ISR: EXCEPTION TRIGGERED\n");

		while(1) {
			__asm__ volatile ("hlt");
		}
	}

	return (uint32_t*)regs;
}
