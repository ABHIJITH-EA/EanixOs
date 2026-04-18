#include "kprintf.h"

void kernel_main(void) {
	vga_init();

	kprintf("Welcome to Ea37NetOS\n");
	kprintf("Decimal: %d\n", 12345);
	kprintf("Negative: %d\n", -42);
	kprintf("Hex: %x\n", 0xDEADBEEF);
	kprintf("Char: %c\n", 'A');
	kprintf("String: %s\n", "Hello Kernel");

    while(1) {
        __asm__ volatile ("hlt");
    }
}
