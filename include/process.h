#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

struct task;

typedef struct process {
    uint32_t pid;
    struct task* main_task;
} process_t;

extern process_t* current_process;

process_t* process_create(void (*entry)());
process_t* process_get_current();


#endif