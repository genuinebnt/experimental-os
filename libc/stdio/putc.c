#include <stdio.h>
#include <kernel/tty.h>

void putc(char c)
{
    terminal_write(&c, 1);
}
