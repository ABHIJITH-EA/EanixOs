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
	task_state_t state;

	uint32_t sleep_ticks;

	int waiting_for_input;

	struct process* process;
} task_t;

void idle_task(void);
void task_init(void);
task_t* task_create(void (*entry)());
uint32_t* task_schedule(uint32_t*);
task_t* task_get_current(void);
void task_set_idle(task_t*);
void task_tick(void);
void task_sleep(uint32_t);

#endif
