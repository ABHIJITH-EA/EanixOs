#include "idt.h"
#include "kprintf.h"
#include "vga.h"

void kernel_main(void) {
	vga_init();

	// kprintf("Welcome to Ea37NetOS\n");

	kprintf("Initializing IDT...\n");
	idt_init();

	// OMG qemu crashing with this
	// __asm__ volatile ("sti");

	kprintf("Triggering exception...\n");

	kprintf("Before exception\n");
	// volatile int zero = 0;
	// int x = 1 / zero;
	__asm__ volatile (
	    "mov $0, %eax\n"
	    "div %eax\n"
	);
	kprintf("After exception\n");

	// (void)x;

    while(1) {
        __asm__ volatile ("hlt");
    }
}
