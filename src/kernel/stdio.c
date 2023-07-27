#include "stdio.h"
#include "stddef.h"
#include "tty.h"

void putc(char c)
{
    terminal_write(&c, 1);
}

static bool print(const char *str, size_t length)
{
    while (*str)
    {
        putc(*str);
        str++;
    }

    return true;
}

#define PRINTF_STATE_NORMAL 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_SPECIFIER 2

void printf(const char *fmt, ...)
{
    int *argp = (int *)&fmt;
    argp = sizeof(fmt) / sizeof(int);
    argp++;

    uint32_t state = PRINTF_STATE_NORMAL;

    while (*fmt)
    {
        switch (state)
        {
        case PRINTF_STATE_NORMAL:
            switch (*fmt)
            {
            case '%':
                state = PRINTF_STATE_LENGTH;
                break;
            default:
                putc('%');
                break;
            }
            break;
        }
        fmt++;
    }
}