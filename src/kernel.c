#include "vga.h"
#include "kprintf.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "timer.h"
#include "keyboard.h"
#include "string.h"


void kernel_main(void) {
	vga_init();

	// kprintf("Welcome to Ea37NetOS\n");

	kprintf("Initializing GDT...\n");
	gdt_init();

	kprintf("Initializing IDT...\n");
	idt_init();

	kprintf("Remapping PIC...\n");
	pic_remap();
	pic_enable_timer();
	pic_enable_keyboard();

	pit_init(100);

	__asm__ volatile ("sti");
	kprintf("Starting timer...\n");

	// kprintf("Sleeping 2 seconds...\n");
	// timer_sleep(200);
	// kprintf("Awake!\n");

	kprintf("> ");

	char cmd[128];
	int idx = 0;

	while(1) {
		if(keyboard_has_input()) {
			char c = keyboard_get_char();

			if(c == '\n') {
				cmd[idx] = '\0';
				kprintf("\n");

				// process command
				if(idx > 0) {
					if(strcmp(cmd, "help") == 0) {
						kprintf("Commands: help clear ticks\n");
					} else if(strcmp(cmd, "clear") == 0) {
						vga_init();
					} else if(strcmp(cmd, "ticks") == 0) {
						kprintf("Ticks: %d\n", timer_get_ticks());
					} else {
						kprintf("Unknown command\n");
					}
				}

				idx = 0;
				kprintf("> ");
			} else if(c == '\b') {
				if(idx > 0) {
					idx--;
					vga_put_char('\b');
				}
			} else {
				if(idx < 127) {
					cmd[idx++] = c;
					vga_put_char(c); // echo
				}
			}
		}

		__asm__ volatile ("hlt");
	}

}
