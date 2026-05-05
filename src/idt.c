#include "idt.h"
#include "kprintf.h"

extern void idt_load(uint32_t);
extern void isr0();
extern void isr32();
extern void isr33();
extern void isr128();

idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t idt_ptr;

static void idt_set_gate(int n, uint32_t handler, uint16_t selector, uint8_t flags) {
	idt[n].offset_low = handler & 0xFFFF;
	idt[n].selector = selector;
	idt[n].zero = 0;
	idt[n].type_attr = flags;
	idt[n].offset_high = (handler >> 16) & 0xFFFF;
}



void idt_init() {
	idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
	idt_ptr.base = (uint32_t)&idt;

	// Clear table
	// for(int i = 0; i < IDT_ENTRIES; i++) {
	// 	idt_set_gate(i, 0);
	// }

	// for(int i = 0; i < IDT_ENTRIES; i++) {
	//     idt[i].offset_low = 0;
	//     idt[i].offset_high = 0;
	//     idt[i].selector = 0;
	//     idt[i].zero = 0;
	//     idt[i].type_attr = 0;
	// }

	idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E); // Divided-by-zero handler
	idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)isr33, 0x08, 0x8E);
	idt_set_gate(128, (uint32_t)isr128, 0x08, 0x8E);

	kprintf("IDT base: %x\n", (uint32_t)&idt);
	kprintf("IDT ptr: %x\n", (uint32_t)&idt_ptr);

	idt_load((uint32_t)&idt_ptr);
}
