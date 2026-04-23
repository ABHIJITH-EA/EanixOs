#ifndef TASK_H
#define  TASK_H

#include <stdint.h>

typedef struct task {
	uint32_t esp; // stack pointer
	struct task* next; // linked list
} task_t;

void task_init(void);
void task_create(void (*entry)());
void task_switch(void);
task_t* task_get_current(void);

#endif
