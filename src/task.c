#include "task.h"
#include "kmalloc.h"
#include "kprintf.h"

#define STACK_SIZE 4096

extern void task_switch_asm(uint32_t* old, uint32_t* new);

static task_t* current = 0;

task_t* task_get_current() {
	return current;
}

void task_init() {
	current = 0;
}

void task_create(void (*entry)()) {
	task_t* task = (task_t*)kmalloc(sizeof(task_t));

	uint32_t stack = (uint32_t)kmalloc(STACK_SIZE);
	uint32_t* sp = (uint32_t*)(stack + STACK_SIZE);

	*(--sp) = (uint32_t)entry; // retunr address

	task->esp = (uint32_t)sp;

	if(!current) {
		current = task;
		current->next = current;
	} else {
		task->next = current->next;
		current->next  = task;
	}

}

void task_switch() {
	if(!current) return;

	// kprintf("S"); 

	task_t* prev = current;
	current = current->next;

	task_switch_asm(&prev->esp, &current->esp);
}
