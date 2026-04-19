.global isr0
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
    popal

    add $4, %esp   # remove return address from stack

    # restore ds
    pop %eax
    mov %ax, %ds
    mov %ax, %es

    popa

    add $8, %esp   # remove int_no + err_code

    iret

hang:
	hlt
	jmp hang
