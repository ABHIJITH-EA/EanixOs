.global task_switch_asm

task_switch_asm:
    mov 4(%esp), %eax   # &prev->esp
    mov 8(%esp), %ebx   # &current->esp

    mov %esp, (%eax)    # save old stack
    mov (%ebx), %esp    # load new stack

    ret