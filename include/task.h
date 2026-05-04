#ifndef TASK_H
#define  TASK_H

#include <stdint.h>

typedef enum {
	TASK_READY,
	TASK_RUNNING,
	TASK_BLOCKED,
	TASK_IDLE
} task_state_t;

typedef struct task {
	uint32_t esp;
	struct task* next;
	task_state_t state
} task_t;

void idle_task(void);
void task_init(void);
void task_create(void (*entry)());
uint32_t* task_schedule(uint32_t*);
task_t* task_get_current(void);
void task_set_idle(task_t*);

#endif
