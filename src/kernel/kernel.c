#include "stddef.h"
#include "string.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a i386-elf compiler"
#endif

enum vga_color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const uint32_t VGA_MEMORY = 0xB8000;

uint8_t terminal_color;
uint16_t *terminal_buffer;

size_t terminal_row;
size_t terminal_column;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | (bg << 4);
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t)uc | ((uint16_t)color << 8);
}

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

void kernel_main()
{
    terminal_init();
    terminal_write_string("hello\nfrom\nthe\nkernel\nthis\nlooks\nlike\nthis\nwill\nwork\nfingers\ncrossed\nthis\nlooks\nmessed\nuphello\nfrom\nthe\nkernel\nthis\nlooks\nlike\nthis\nwill\nwork\nfingers\ncrossed\nthis\nlooks\nmessed\nuphello\nfrom\nthe\nkernel\nthis\nlooks\nlike\nthis\nwill\nwork\nfingers\ncrossed\nthis\nlooks\nmessed\nuphello\nfrom\nthe\nkernel\nthis\nlooks\nlike\nthis\nwill\nwork\nfingers\ncrossed\nthis\nlooks\nmessed\nup");
}