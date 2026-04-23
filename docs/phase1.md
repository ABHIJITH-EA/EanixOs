GCC is trying to link a 64-bit libgcc, but we are building a 32-bit kernel

But My system has 64-bit GCC does NOT have 32-bit libraries installed

Quick Fix: sudo apt install gcc-multilib

Cleaner OSDev Approach is to eventually, we should use a cross-compiler: i686-elf-gcc
