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
		for(volatile int i = 0; i < 5000000; i++);
	}
}

void taskB() {
	while(1) {
		terminal_write("B");
		for(volatile int i = 0; i < 5000000; i++);
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
	
	task_create(idle_task);
	task_create(taskA);
	task_create(taskB);

	// __asm__ volatile ("sti");

	task_t* first = task_get_current();

	__asm__ volatile(
		"mov %0, %%esp\n"
		"pop %%eax\n"	// ds
		"mov %%ax, %%ds\n"
		"mov %%ax, %%es\n"
		"popa\n"
		"add $8, %%esp\n"	// skip int_no + err_code
		"iret\n"
		:
		: "r"(first->esp)
	);

	while(1) {
		__asm__ volatile ("hlt");
	}

}
