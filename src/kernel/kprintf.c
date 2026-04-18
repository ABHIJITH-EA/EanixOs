#include <stdarg.h>
#include <stdint.h>
#include "vga.h"
#include "kprintf.h"


static void print_string(const char* str) {
	vga_write(str);
}

static void print_int(int value) {
	char buffer[12];
	int i = 0;

	if(value == 0) {
		vga_put_char('0');
		return;
	}

	int is_negative = 0;
	if(value < 0) {
		is_negative = 1;
		value = -value;
	}

	while (value > 0) {
		buffer[i++] = '0' + (value % 10);
		value /= 10;
	}

	if(is_negative) {
		buffer[i++] = '-';
	}

	// reverse
	for(int j = i - 1; j >=0; j--) {
		vga_put_char(buffer[j]);
	}
}

static void print_hex(uint32_t value) {
	char hex_chars[] = "0123456789ABCDEF";

	vga_write("0x");

	for(int i = 28; i >= 0; i -= 4) {
		uint8_t digit = (value >> i) & 0xF;
		vga_put_char(hex_chars[digit]);
	}
}


void kprintf(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	for(int i = 0; fmt[i] != '\0'; i++) {
		if(fmt[i] == '%') {
			i++;

			switch(fmt[i]) {
				case 'd': {
					int val = va_arg(args, int);
					print_int(val);
					break;
				}

				case 'x': {
					uint32_t val = va_arg(args, uint32_t);
					print_hex(val);
					break;
				}

				case 's': {
					char* str = va_arg(args, char*);
					print_string(str);
					break;
				}

				case 'c': {
					char c = (char)va_arg(args, int);
					vga_put_char(c);
					break;
				}

				case '%': {
					vga_put_char('%');
					break;
				}

				default:
				vga_put_char('%');
				vga_put_char(fmt[i]);
				break;
			}
		} else {
			vga_put_char(fmt[i]);
		}
	}

	va_end(args);
}
