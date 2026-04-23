CC = gcc
CFLAGS = -ffreestanding -m32 -O2 -Wall -Wextra \
         -fno-pic -fno-pie -fno-stack-protector -mno-red-zone \
         -Iinclude
LDFLAGS = -T linker.ld -ffreestanding -m32 -nostdlib -nostartfiles -nodefaultlibs -nostdinc -Wl,--build-id=none -static

SRC = src/kernel.c src/boot.S src/drivers/vga.c src/kernel/kprintf.c \
	src/idt.c src/isr.c src/isr_asm.S src/idt_load.S src/gdt.c src/gdt_flush.S \
	src/pic.c src/pit.c src/timer.c src/keyboard.c src/string.c src/terminal.c \
	src/kmalloc.c src/task.c src/task_switch.S

# OBJ = $(SRC:.c=.o)
# OBJ := $(OBJ:.S=.o)

OBJ = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRC)))

all: os.iso

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.S
	$(CC) $(CFLAGS) -c $< -o $@


kernel.bin: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ src/boot.o $(filter-out src/boot.o,$(OBJ)) -lgcc

os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	cp boot/grub/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso -d /usr/lib/grub/i386-pc

run: os.iso
	qemu-system-i386 -boot d -cdrom os.iso

clean:
	rm -rf *.bin *.iso iso src/*.o src/kernel/*.o src/drivers/*.o
