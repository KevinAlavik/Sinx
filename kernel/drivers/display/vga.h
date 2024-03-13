#ifndef __VGA_H__
#define __VGA_H__

#include <printf.h>
#include <stdint.h>

#include <math.h>
#include <drivers/serial/serial.h>

#include "framebuffer.h"

int vga_initialize(framebuffer_t* fb);

void put_pixel(uint32_t x, uint32_t y, uint32_t color);
void flush(uint32_t hex);

// Functions for converting colors into hex.
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void text_mode_warning();

void draw_triangle_with_gradient(uint32_t hex_color1, uint32_t hex_color2, uint32_t hex_color3);

#endif // __VGA_H__
