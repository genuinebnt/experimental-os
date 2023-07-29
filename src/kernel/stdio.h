#pragma once
#include "stddef.h"

void putc(char c);
void puts(char *c);
void print(char *c);
void printf(const char *format, ...);
int *printf_number(int *argp, int length, bool sign, int radix);