#include <stdint.h>
#include "vga.h"
#include "io.h"


#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/*
 * VGA text buffer memory.
 * 0xB8000 = Screen character buffer
*/
static uint16_t* const VGA_MEMORY = (uint16_t*)0xB8000;

static uint8_t color = 0x07;
static uint16_t cursor_row = 0;
static uint16_t cursor_col = 0;

static void vga_scroll(void);
static void vga_update_cursor(void);
static void vga_enable_cursor(uint8_t, uint8_t);

static uint16_t vga_entry(char c, uint8_t color) {
	return (uint16_t)c | ((uint16_t) color << 8);

}

void vga_init() {
	cursor_row = 0;
	cursor_col = 0;

	for(uint16_t y = 0; y < VGA_HEIGHT; y++) {
		for(uint16_t x = 0; x < VGA_WIDTH; x++) {
			VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(' ', color);
		}
	}

	vga_update_cursor();
}

void vga_put_char(char c) {
	if(c == '\n') {
		cursor_col = 0;
		cursor_row++;

		if(cursor_row >= VGA_HEIGHT) {
			vga_scroll();
		}

		return;
	}

	VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_col] = vga_entry(c, color);

	cursor_col++;

	if(cursor_col >= VGA_WIDTH) {
		cursor_col = 0;
		cursor_row++;
	}

	if(cursor_row >= VGA_HEIGHT) {
		// cursor_row = 0;
		vga_scroll();
	}

	// vga_enable_cursor(0, 15);
	// vga_enable_cursor(14, 15); // underline cursor
	vga_enable_cursor(8, 15); // half block cursor
	//
	vga_update_cursor();
}

void vga_write(const char *str) {
	for(int idx = 0; str[idx] != '\0'; idx++) {
		vga_put_char(str[idx]);
	}
}

static void vga_scroll(void) {
	for(int y = 1; y < VGA_HEIGHT; y++) {
		for(int x = 0; x < VGA_WIDTH; x++) {
			VGA_MEMORY[(y - 1) * VGA_WIDTH + x] =
				VGA_MEMORY[y * VGA_WIDTH + x];
		}
	}

	// clear last row
	for(int x = 0; x < VGA_WIDTH; x++) {
		VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
			vga_entry(' ', color);
	}

	cursor_row = VGA_HEIGHT - 1;
}

static void vga_enable_cursor(uint8_t start, uint8_t end) {

	outb(0x3D4, 0x0A);
	outb(0x3D5, start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, end);
}

static void vga_update_cursor(void) {
	uint16_t pos = cursor_row * VGA_WIDTH + cursor_col;

	// High byte
	outb(0x3D4, 14);
	outb(0x3D5, (pos>> 8) & 0xFF);

	// Low byte
	outb(0x3D4, 15);
	outb(0x3D5, pos & 0xFF);
}
