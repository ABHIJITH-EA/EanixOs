#include "process.h"
#include "task.h"
#include "kmalloc.h"

static uint32_t next_pid = 1;
process_t* current_process = 0;

process_t* process_create(void (*entry)()) {
    process_t* proc = (process_t*)kmalloc(sizeof(process_t));

    proc->pid = next_pid++;

    task_t* t = task_create(entry);
    t->process = proc;

    proc->main_task = t;

    return proc;
}

process_t* process_get_current() {
    return current_process;
}