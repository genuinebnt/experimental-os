#pragma once
#include "stddef.h"

void putc(char c);
void puts(const char *c);
static bool print(const char *c, size_t length);
void printf(const char *fmt, ...);