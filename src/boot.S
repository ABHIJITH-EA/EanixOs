.section .multiboot
.align 4
.long 0x1BADB002
.long 0x0
.long -(0x1BADB002)

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.extern kernel_main

_start:
    # Setup stack
    mov $stack_top, %esp
    xor %ebp, %ebp

    # Align stack to 16 bytes (IMPORTANT)
    and $0xFFFFFFF0, %esp

    # Call kernel
    call kernel_main

hang:
    cli
    hlt
    jmp hang

.section .note.GNU-stack,"",@progbits
