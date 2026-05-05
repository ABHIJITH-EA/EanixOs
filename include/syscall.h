#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

void sys_write(char* str);
void sys_sleep(uint32_t ticks);
void sys_write_char(char ch);

#endif