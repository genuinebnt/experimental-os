#include <stdio.h>

__attribute__((__noreturn__)) void abort()
{
    printf("Kernel panic: abort()\n");
    asm volatile("hlt");
    while (1)
    {
    }

    __builtin_unreachable();
}