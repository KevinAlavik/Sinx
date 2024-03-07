#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>

#include "framebuffer.h"

int vga_initialize(framebuffer_t* fb);

void put_pixel(uint32_t x, uint32_t y, uint32_t color);
void flush(uint8_t r, uint8_t g, uint8_t b);

// Functions for converting colors into hex.
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif // __VGA_H__
