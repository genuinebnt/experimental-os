#include "tty.h"
#include "vga.h"
#include "string.h"

void terminal_init()
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putentryat(const char c, uint8_t terminal_color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, terminal_color);
}

void terminal_scroll()
{
    char c;
    for (size_t line = 1; line < VGA_HEIGHT; line++)
    {
        for (size_t loop = 0; loop < VGA_WIDTH * 2; loop++)
        {
            c = terminal_buffer[loop];
            terminal_buffer[loop - (VGA_WIDTH * 2)] = c;
        }
    }
}

void terminal_delete_last_line()
{
    // memset(terminal_buffer + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1), 0, VGA_WIDTH);
    for (size_t i = 0; i < VGA_WIDTH * 2; i++)
    {
        terminal_buffer[i + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1)] = 0;
    }
}

void terminal_putchar(const char c)
{
    if (c == '\n')
    {
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_scroll();
            terminal_delete_last_line();
            terminal_row = VGA_HEIGHT - 1;
        }
        terminal_column = 0;
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_scroll();
            terminal_delete_last_line();
            terminal_row = VGA_HEIGHT - 1;
        }
    }
}

void terminal_write(const char *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        terminal_putchar(data[i]);
    }
}

void terminal_write_string(const char *data)
{
    terminal_write(data, strlen(data));
}