#include "terminal.h"
#include "task.h"
#include <stdint.h>

uint32_t syscall_handler(uint32_t* regs) {
    uint32_t eax = regs[8]; // eax from pusha
    uint32_t ebx = regs[5];
    // uint32_t ecx = regs[7];
    // uint32_t edx = regs[6];

    switch(eax) {
        case 1: // SYS_WRITE
         terminal_write((char*)ebx);
         break;

         case 2: //SYS_SLEEP
            task_sleep(ebx);
            break;

        case 3:
            terminal_putchar((char) ebx);
            break;

        default:
            terminal_write("unknown syscall\n");
            break;
    }

    return (uint32_t)regs;
}

void sys_write(char* str) {
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(1), "b"(str)
    );
}

void sys_sleep(uint32_t ticks) {
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(2), "b"(ticks)
    );
}

void sys_write_char(char ch) {
    __asm__ volatile(
        "int $0x80"
        :
        : "a"(3), "b"((uint32_t)ch) 
    );
}