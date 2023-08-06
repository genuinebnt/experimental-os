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
    terminal_init();
    char *src = "hello world";
    char dst[14];
    int bytes = strncpy(dst, src, strlen(src));
    printf("Destination buffer: %s\n Source buffer: %s\n Bytes copied: %d", dst, src, bytes);
    for (size_t i = 0; i < 50; i++)
    {
        printf("Hello %d\n", i);
    }
}