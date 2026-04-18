#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void vga_init();
void vga_put_char(char c);
void vga_write(const char* str);
// void vga_scroll();

#endif
