#include <stddef.h>
#include <string.h>

int strcpy(char *dst, const char *src)
{
    size_t i;
    for (i = 0; i < strlen(src) && src[i] != '\0'; i++)
    {
        dst[i] = src[i];
    }

    dst[i] = '\0';
    return i;
}

int strncpy(char *dst, const char *src, size_t size)
{
    size_t i;
    for (i = 0; i < size && src[i] != '\0'; i++)
    {
        dst[i] = src[i];
    }

    dst[i] = '\0';
    return i;
}