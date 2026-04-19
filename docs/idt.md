Each entry:

	[handler address split into 2 parts]
	[segment selector]
	[flags]



qemu shrinking when trying to setup the first interrupt(Division by zero) it was becauze
GDT is missing or wrong since we cannot use `selector = 0x08;` without a valid GDT loaded.
