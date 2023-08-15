#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a i386-elf compiler"
#endif

void kernel_main()
{
    printf("Hello world!\n");
}