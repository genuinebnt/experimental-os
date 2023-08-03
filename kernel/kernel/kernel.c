#include <stdio.h>
#include <kernel/tty.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a i386-elf compiler"
#endif

void kernel_main()
{
    terminal_init();
    printf("Formatted %s %c %d %i %x %p %o %hd\r\n", "Hello world", 'z', 1234, 5678, 0xbeef, 0123, (short)27, (short)-42);
}