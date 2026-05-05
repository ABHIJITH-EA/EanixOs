#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_push(char);
char keyboard_get_char();
int keyboard_has_input();
char keyboard_getchar_blocking();

#endif
