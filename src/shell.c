#include "keyboard.h"
#include "syscall.h"

void shell() {
    char buffer[128];
    int i = 0;

    sys_write("> ");

    while(1) {
        
        char c = keyboard_getchar_blocking();
        
        if (c == '\n') {
            buffer[i] = 0;
            sys_write("\n> ");
            sys_write(buffer);
            sys_write("\n");

            i = 0;

            sys_write("> ");

        } else if (c == '\b') {
        } else {
            if((unsigned int)i < sizeof(buffer) - 1) {
                buffer[i++] = c;
            }
            sys_write_char(c);
        }
    }
}