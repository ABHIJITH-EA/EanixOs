ENTRY(_start)

SECTIONS
{
    . = 1M;

    .text : ALIGN(4)
    {
        KEEP(*(.multiboot))   /* MUST BE FIRST */
        *(.text*)
    }

    .rodata : ALIGN(4)
    {
        *(.rodata*)
    }

    .data : ALIGN(4)
    {
        *(.data*)
    }

    .bss : ALIGN(4)
    {
        *(.bss*)
        *(COMMON)
    }
}