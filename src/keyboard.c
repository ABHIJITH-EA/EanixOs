#include "keyboard.h"
#include "task.h"

#define BUFFER_SIZE 256

static char buffer[BUFFER_SIZE];
static int head = 0;
static int tail = 0;

void keyboard_push(char c) {
	int next = (head + 1) % BUFFER_SIZE;

	if(next != tail) {
		buffer[head] = c;
		head = next;
	}
}

int keyboard_has_input() {
	return head != tail;
}

char keyboard_get_char() {
	if(head == tail) return 0;

	char c = buffer[tail];
	tail = (tail + 1) % BUFFER_SIZE;
	return c;
}

char keyboard_getchar_blocking() {
	while (!keyboard_has_input())
	{
		task_sleep(1);
	}
	
	return keyboard_get_char();
}
