#include <stdio.h>

void print(char *str)
{
    while (*str)
    {
        putc(*str);
        str++;
    }
}
