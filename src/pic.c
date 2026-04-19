#include "io.h"

#define PIC1 0x20
#define PIC2 0xA0

#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

void pic_remap() {
	uint8_t a1 = inb(PIC1_DATA);
	uint8_t a2 = inb(PIC2_DATA);

	// starts initialization
	outb(PIC1_COMMAND, 0x11);
	outb(PIC2_COMMAND, 0x11);

	// setup offsets
	outb(PIC1_DATA, 0x20); // IRQ0 -> 32
	outb(PIC2_DATA, 0x28); // IRQ8 -> 40

	// setup cascading
	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);

	// environment info
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);

	// restore masks
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void pic_enable_timer() {
	uint8_t mask = inb(0x21);
	mask &= ~(1 << 0); // Enable IRQ0
	outb(0x21, mask);
}
