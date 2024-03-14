#include "vga.h"
#include "text.h"
#include <math.h>

framebuffer_t *framebuffer;

int vga_initialize(framebuffer_t *fb)
{
    framebuffer = fb;
    if (!framebuffer)
    {
        return 1;
    }
    return 0;
}

void put_pixel(uint32_t x, uint32_t y, uint32_t hex_color)
{
    uint8_t r = (hex_color >> 16) & 0xFF;
    uint8_t g = (hex_color >> 8) & 0xFF;
    uint8_t b = hex_color & 0xFF;
    uint8_t a = (hex_color >> 24) & 0xFF;

    uint32_t *pixel =
        (uint32_t *)(framebuffer->address + x * (framebuffer->bpp >> 3) +
                     y * framebuffer->pitch);
    uint32_t current_color = *pixel;

    uint8_t current_r = (current_color >> 16) & 0xFF;
    uint8_t current_g = (current_color >> 8) & 0xFF;
    uint8_t current_b = current_color & 0xFF;
    uint8_t current_alpha = (current_color >> 24) & 0xFF;

    uint16_t final_alpha = current_alpha + ((255 - current_alpha) * a) / 255;

    uint8_t final_r = ((r * a) / 255) + ((current_r * current_alpha * (255 - a)) / 255);
    uint8_t final_g = ((g * a) / 255) + ((current_g * current_alpha * (255 - a)) / 255);
    uint8_t final_b = ((b * a) / 255) + ((current_b * current_alpha * (255 - a)) / 255);

    *pixel = (final_alpha << 24) | (final_r << 16) | (final_g << 8) | final_b;
}

void flush(uint32_t hex)
{
    for (uint32_t i = 0; i < framebuffer->width; i++)
    {
        for (uint32_t j = 0; j < framebuffer->height; j++)
        {
            put_pixel(i, j, hex);
        }
    }
}

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return 0xFF000000 | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void text_mode_warning()
{
    terminal_initialize();
    outb8(0x3D4, 0x0A);
    outb8(0x3D5, 0x20);
    terminal_writestring("You are currently booted into text mode? Please try to reboot");
}
