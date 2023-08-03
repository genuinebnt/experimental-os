#include <string.h>

void memset(void *dstptr, int value, size_t size)
{
    unsigned char *dst = (unsigned char *)dstptr;
    for (size_t i = 0; i < size; i++)
    {
        dst[i] = (unsigned char)value;
    }
}