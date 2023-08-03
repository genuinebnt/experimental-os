#include <stdint.h>
#include <stdio.h>

#define PRINTF_STATE_NORMAL 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_LENGTH_SHORT 2
#define PRINTF_STATE_LENGTH_LONG 3
#define PRINTF_STATE_SPECIFIER 4
#define PRINTF_STATE_LENGHT_LONG_LONG 5

#define PRINTF_LENGTH_DEFAULT 0
#define PRINTF_LENGTH_SHORT_SHORT 1
#define PRINTF_LENGTH_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4

void printf(const char *format, ...)
{
    int currentState = PRINTF_STATE_NORMAL;
    int length = PRINTF_LENGTH_DEFAULT;
    int radix = 10;
    bool sign = false;

    int *argp = (int *)&format;
    argp++;

    while (*format)
    {
        switch (currentState)
        {
        case PRINTF_STATE_NORMAL:
            switch (*format)
            {
            case '%':
                currentState = PRINTF_STATE_LENGTH;
                break;

            default:
                putc(*format);
                break;
            }
            break;
        case PRINTF_STATE_LENGTH:
            switch (*format)
            {
            case 'h':
                length = PRINTF_LENGTH_SHORT;
                currentState = PRINTF_STATE_LENGTH_SHORT;
                break;
            case 'l':
                length = PRINTF_LENGTH_LONG;
                currentState = PRINTF_STATE_LENGTH_LONG;
                break;
            default:
                goto PRINTF_STATE_SPECIFIER_;
            }
            break;
        case PRINTF_STATE_LENGTH_SHORT:
            if (*format == 'h')
            {
                length = PRINTF_LENGTH_SHORT_SHORT;
                currentState = PRINTF_STATE_SPECIFIER;
            }
            else
            {
                goto PRINTF_STATE_SPECIFIER_;
            }
            break;
        case PRINTF_STATE_LENGTH_LONG:
            if (*format == 'l')
            {
                length = PRINTF_LENGTH_LONG_LONG;
                currentState = PRINTF_STATE_SPECIFIER;
            }
            else
            {
                goto PRINTF_STATE_SPECIFIER_;
            }
            break;
        case PRINTF_STATE_SPECIFIER:
        PRINTF_STATE_SPECIFIER_:
            switch (*format)
            {
            case 'c':
                putc((char)*argp);
                argp++;
                break;
            case 's':
                print(*(char **)argp);
                argp++;
                break;
            case '%':
                putc('%');
                break;
            case 'd':
            case 'i':
                radix = 10;
                sign = true;
                argp = printf_number(argp, length, sign, radix);
                break;
            case 'u':
                radix = 10;
                sign = false;
                argp = printf_number(argp, length, sign, radix);
                break;
            case 'x':
            case 'X':
            case 'p':
                radix = 16;
                sign = false;
                argp = printf_number(argp, length, sign, radix);
                break;
            case 'o':
                radix = 8;
                sign = false;
                argp = printf_number(argp, length, sign, radix);
            default:
                break;
            }

            currentState = PRINTF_STATE_NORMAL;
            length = PRINTF_LENGTH_DEFAULT;
            radix = 10;
            sign = false;
            break;
        }
        format++;
    }
}

const char g_hexChars[] = "0123456789abcdef";

int *printf_number(int *argp, int length, bool sign, int radix)
{
    char buffer[32];
    unsigned long long number;
    int number_sign = 1;
    int pos = 0;

    switch (length)
    {
    case PRINTF_LENGTH_SHORT_SHORT:
    case PRINTF_LENGTH_SHORT:
    case PRINTF_LENGTH_DEFAULT:
        if (sign)
        {
            int n = *argp;
            if (n < 0)
            {
                n = -n;
                number_sign = -1;
            }
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned int *)argp;
        }
        argp++;
        break;
    case PRINTF_LENGTH_LONG:
        if (sign)
        {
            long int n = *(long int *)argp;
            if (n < 0)
            {
                n = -n;
                number_sign = -1;
            }
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned long int *)argp;
        }
        argp += 2;
        break;
    case PRINTF_LENGTH_LONG_LONG:
        if (sign)
        {
            long long int n = *(long long int *)argp;
            if (n < 0)
            {
                n = -n;
                number_sign = -1;
            }
            number = (unsigned long long)n;
        }
        else
        {
            number = *(unsigned long long int *)argp;
        }
        argp += 4;
        break;
    }

    do
    {
        uint32_t rem = number % radix;
        number /= radix;
        buffer[pos++] = g_hexChars[rem];
    } while (number > 0);

    if (sign && number_sign < 0)
    {
        buffer[pos++] = '-';
    }

    while (--pos >= 0)
    {
        putc(buffer[pos]);
    }

    return argp;
}