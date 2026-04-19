.global isr0
.extern isr_handler

isr0:
	cli

	# Save all general-purpose registers to prevent corrupting the interrupted code
	pushal
	# pushl $0	# fake error code
	# pushl $0	# interrupt number (optional)



    # mov $0xB8000, %eax
    # movb $'E', (%eax)
    # movb $0x04, 1(%eax)

    call isr_handler

    # Restore all general-purpose registers
    popal

    # add $8, %esp   # remove return address from stack

    iret

hang:
	hlt
	jmp hang
