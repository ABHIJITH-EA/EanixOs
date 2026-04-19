#include "vga.h"
#include "kprintf.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "pit.h"
#include "timer.h"

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

	pit_init(100);

	__asm__ volatile ("sti");
	kprintf("Starting timer...\n");

	kprintf("Sleeping 2 seconds...\n");
	timer_sleep(200);
	kprintf("Awake!\n");

	// kprintf("Triggering exception...\n");

	// kprintf("Before exception\n");

	// volatile int zero = 0;
	// int x = 1 / zero;

	// __asm__ volatile (
	//     "mov $0, %eax\n"
	//     "div %eax\n"
	// );

	// kprintf("After exception\n");

	// (void)x;

	// __asm__ volatile ("int $0");

    while(1) {
        __asm__ volatile ("hlt");
    }
}
