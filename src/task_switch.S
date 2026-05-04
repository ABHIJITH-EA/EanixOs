.global task_switch_asm

task_switch_asm:
    # Arguments:
    # old = 4(%esp)
    # new = 8(%esp)

    mov 4(%esp), %eax   # eax = &old->esp
    mov 8(%esp), %edx   # edx = &new->esp

    # Save registers (current task)
    pusha

    # Save current ESP into old task
    mov %esp, (%eax)

    # Load next task ESP
    mov (%edx), %esp

    # Restore registers (next task)
    popa

    ret