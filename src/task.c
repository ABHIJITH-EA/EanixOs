#include "task.h"
#include "kmalloc.h"
#include "kprintf.h"

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

uint32_t* task_switch(uint32_t* current_esp) {
	if(!current) return current_esp;

	current->esp = (uint32_t)current_esp;
	current = current->next;

	return (uint32_t*)current->esp;
}

void idle_task() {
	while (1)
	{
		__asm__ volatile("hlt");
	}
	
}