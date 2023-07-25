#pragma once
#include "stddef.h"

size_t strlen(const char *str);
void memcpy(const void *srcptr, void *dstptr, size_t size);
void memset(void *dstptr, int value, size_t size);