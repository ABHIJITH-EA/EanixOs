#include "terminal.h"
#include "vga.h"

void terminal_init() {
	vga_init();
}

void terminal_putchar(char c) {
	if(c == '\n') {
		vga_put_char('\n');
	} else if (c == '\b') {
		// TODO: proper backspace handling
	} else {
		vga_put_char(c);
	}
}

void terminal_write(const char * str) {
	for(int idx = 0; str[idx]; idx++) {
		terminal_putchar(str[idx]);
	}
}
