#include "terminal.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    } else {
        terminal_buffer[terminal_row * VGA_WIDTH + terminal_column++] = vga_entry(c, terminal_color);
        if (terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row = 0;
            }
        }
    }
}

void terminal_writestring(const char *data) {
    size_t len = strlen(data);
    for (size_t i = 0; i < len; i++) {
        terminal_putchar(data[i]);
    }
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb8(0x3D4, 0x0A);
	outb8(0x3D5, (inb8(0x3D5) & 0xC0) | cursor_start);

	outb8(0x3D4, 0x0B);
	outb8(0x3D5, (inb8(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outb8(0x3D4, 0x0A);
	outb8(0x3D5, 0x20);
}
