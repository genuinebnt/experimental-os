#pragma once
#include <stddef.h>

size_t strlen(const char *str);
void memcpy(const void *srcptr, void *dstptr, size_t size);
void memset(void *dstptr, int value, size_t size);
int strcpy(char *dst, const char *src);
int strncpy(char *dst, const char *src, size_t size);