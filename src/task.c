#include "task.h"
#include "kmalloc.h"
#include "kprintf.h"
#include <stddef.h>

#define STACK_SIZE 4096

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
	uint32_t* sp = (uint32_t*)((stack + STACK_SIZE) & ~0xF);

	*(--sp) = 0x202; // eflags
	*(--sp) = 0x08;	 // cs
	*(--sp) = (uint32_t)entry; // EIP

	*(--sp) = 0; // err_code
	*(--sp) = 32; // int_no	
	

	// pusha registers (REVERSE ORDER)
	*(--sp) = 0; // edi
	*(--sp) = 0; // esi
	*(--sp) = 0; // ebp
	*(--sp) = 0; // esp
	*(--sp) = 0; // ebx
	*(--sp) = 0; // edx
	*(--sp) = 0; // ecx
	*(--sp) = 0; // eax
	
	*(--sp) = 0x10;	// ds

	task->esp = (uint32_t)sp;
	task->state = TASK_READY;
	task->sleep_ticks = 0;

	if(!current) {
		current = task;
		task->next = task;
	} else {
		task_t* temp = current;

		while (temp->next != current)
		{
			temp = temp->next;
		}
		
		temp->next = task;
		task->next  = current;
	}

}

uint32_t* task_schedule(uint32_t* current_esp) {
	if(!current) return current_esp;

	// save current context
	current->esp = (uint32_t)current_esp;

	if(current->state == TASK_RUNNING)
		current->state = TASK_READY;

	task_t* next = current->next;
	task_t* idle = NULL;

	while (1) {
		if(next->state == TASK_READY) break;
		
		if(next->state == TASK_IDLE)
			idle = next;

		next = next->next;

		if(next == current) break;
	}

	if(next->state != TASK_READY) {
		if (idle) next = idle;
		else next = current;
	}

	current = next;
	current->state = TASK_RUNNING;

	return (uint32_t*)current->esp;
}

void idle_task() {
	while (1)
	{
		__asm__ volatile("hlt");
	}
	
}

void task_set_idle(task_t* task) {
	task->state = TASK_IDLE;
}

void task_sleep(uint32_t ticks) {
	if(!current) return;

	current->sleep_ticks = ticks;
	current->state = TASK_BLOCKED;

	__asm__ volatile("int $32");
}

void task_tick() {
	if (!current) return;

	task_t* t = current;

	do {
		if(t->state == TASK_BLOCKED && t->sleep_ticks > 0) {
			t->sleep_ticks--;

			if(t->sleep_ticks == 0) {
				t->state = TASK_READY;
			}
		}

		t = t->next;
	} while(t != current);
}