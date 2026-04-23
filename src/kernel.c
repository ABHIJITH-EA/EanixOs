#include "vga.h"
#include "kprintf.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "timer.h"
#include "keyboard.h"
#include "string.h"
#include "terminal.h"
#include "task.h"

void taskA() {
	while(1) {
		terminal_write("A");
		for(volatile int i = 0; i < 1000000; i++);
		task_switch();
	}
}

void taskB() {
	while(1) {
		terminal_write("B");
		for(volatile int i = 0; i < 1000000; i++);
		task_switch();
	}
}

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

	kprintf("Initializing tasks...\n");
	task_init();

	task_create(taskA);
	task_create(taskB);

	__asm__ volatile ("sti");
	task_t* first = task_get_current();

	__asm__ volatile(
		"mov %0, %%esp\n"
		"ret\n"
		:
		: "r"(first->esp)
	);

	// kprintf("Starting timer...\n");

	// kprintf("Sleeping 2 seconds...\n");
	// timer_sleep(200);
	// kprintf("Awake!\n");

	// kprintf("> ");

	// char cmd[128];
	// int idx = 0;

	while(1) {
	// 	if(keyboard_has_input()) {
	// 		char c = keyboard_get_char();

	// 		if(c == '\n') {
	// 			cmd[idx] = '\0';
	// 			kprintf("\n");

	// 			// process command
	// 			if(idx > 0) {
	// 				if(strcmp(cmd, "help") == 0) {
	// 					kprintf("Commands: help clear ticks\n");
	// 				} else if(strcmp(cmd, "clear") == 0) {
	// 					vga_init();
	// 				} else if(strcmp(cmd, "ticks") == 0) {
	// 					kprintf("Ticks: %d\n", timer_get_ticks());
	// 				} else {
	// 					kprintf("Unknown command\n");
	// 				}
	// 			}

	// 			idx = 0;
	// 			kprintf("> ");
	// 		} else if(c == '\b') {
	// 			if(idx > 0) {
	// 				idx--;
	// 				terminal_putchar('\b');
	// 			}
	// 		} else {
	// 			if(idx < 127) {
	// 				cmd[idx++] = c;
	// 				terminal_putchar(c); // echo
	// 			}
	// 		}
	// 	}

		__asm__ volatile ("hlt");
	}

}
