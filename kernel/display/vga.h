#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>
#include <stddef.h>


#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_WHITE = 15,
};

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
uint16_t vga_entry(char uc, uint8_t color);

#endif // __VGA_H__
