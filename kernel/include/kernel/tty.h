#pragma once

#include <stdint.h>
#include <stddef.h>

void terminal_init();
void terminal_putentryat(const char c, uint8_t terminal_color, size_t x, size_t y);
void terminal_scroll();
void terminal_delete_last_line();
void terminal_putchar(const char c);
void terminal_write(const char *data, size_t len);
void terminal_write_string(const char *data);