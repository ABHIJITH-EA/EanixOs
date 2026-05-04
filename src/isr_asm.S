.global isr0
.global isr32
.global isr33

.extern isr_handler

isr0:
	cli

	# Save all general-purpose registers to prevent corrupting the interrupted code
	# pushal

	pushl $0	# fake error code
	pushl $0	# interrupt number

	pusha		# push general registers

	mov %ds, %ax
	push %eax

	mov $0x10, %ax # kernel data segment
	mov %ax, %ds
	mov %ax, %es

	push %esp # pass pointer to registers_t

    # mov $0xB8000, %eax
    # movb $'E', (%eax)
    # movb $0x04, 1(%eax)

    call isr_handler

    # Restore all general-purpose registers
    # popal

    add $4, %esp   # remove return address from stack

    # restore ds
    pop %eax
    mov %ax, %ds
    mov %ax, %es

    popa

    add $8, %esp   # remove int_no + err_code

    iret

isr32:
    cli
    push $0
    push $32
    pusha

    mov %ds, %ax
    push %eax

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es

    push %esp
    call isr_handler

    add $4, %esp     # remove arg

    mov %eax, %esp   # SWITCH


    pop %eax
    mov %ax, %ds
    mov %ax, %es

    popa
    add $8, %esp

    movb $0x20, %al
    outb %al, $0x20

    // sti
    iret

isr33:
    cli

    pushl $0
    pushl $33

    pusha

    mov %ds, %ax
    push %eax

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es

    push %esp
    call isr_handler

    add $4, %esp

    pop %eax
    mov %ax, %ds
    mov %ax, %es

    popa
    add $8, %esp

    movb $0x20, %al
    outb %al, $0x20   # EOI

    sti
    iret

hang:
	hlt
	jmp hang
