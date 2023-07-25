#include "string.h"

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}

void memcpy(const void *srcptr, void *dstptr, size_t size)
{
    unsigned char *dst = (unsigned char *)dstptr;
    const unsigned char *src = (const unsigned char *)srcptr;
    for (size_t i = 0; i < size; i++)
    {
        dst[i] = src[i];
    }
}

void memset(void *dstptr, int value, size_t size)
{
    unsigned char *dst = (unsigned char *)dstptr;
    for (size_t i = 0; i < size; i++)
    {
        dst[i] = (unsigned char)value;
    }
}