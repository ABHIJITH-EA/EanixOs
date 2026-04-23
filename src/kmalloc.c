#include "kmalloc.h"

#define HEAP_START 0x01000000

static uint32_t heap_top = HEAP_START;

void* kmalloc(uint32_t size) {
	void* addr = (void*)heap_top;
	heap_top += size;

	return addr;
}
