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

typedef struct {
    int x;
    int y;
} Point;

void swap_points(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

void draw_triangle_with_gradient(uint32_t hex_color1, uint32_t hex_color2, uint32_t hex_color3) {
    int side = framebuffer->height / 2;
    int half_height = (int)(side * sqrt(3) / 2);

    Point vertices[3] = {
        {framebuffer->width / 2, (framebuffer->height - half_height) / 2},
        {framebuffer->width / 4, (framebuffer->height + half_height) / 2},
        {3 * framebuffer->width / 4, (framebuffer->height + half_height) / 2}
    };

    if (vertices[0].y > vertices[1].y) swap_points(&vertices[0], &vertices[1]);
    if (vertices[1].y > vertices[2].y) swap_points(&vertices[1], &vertices[2]);
    if (vertices[0].y > vertices[1].y) swap_points(&vertices[0], &vertices[1]);

    double slope1 = (double)(vertices[1].x - vertices[0].x) / (vertices[1].y - vertices[0].y);
    double slope2 = (double)(vertices[2].x - vertices[0].x) / (vertices[2].y - vertices[0].y);
    double slope3 = (double)(vertices[2].x - vertices[1].x) / (vertices[2].y - vertices[1].y);

    double x1 = vertices[0].x;
    double x2 = vertices[0].x;

    for (int y = vertices[0].y; y <= vertices[1].y; ++y) {
        int minx = (int)ceil(x1);
        int maxx = (int)floor(x2);

        double delta1 = (y - vertices[0].y) / (double)(vertices[1].y - vertices[0].y);
        double delta2 = (y - vertices[0].y) / (double)(vertices[2].y - vertices[0].y);

        uint32_t color1 = rgb(
            (uint8_t)(((1 - delta1) * ((hex_color1 >> 16) & 0xFF)) + (delta1 * ((hex_color2 >> 16) & 0xFF))),
            (uint8_t)(((1 - delta1) * ((hex_color1 >> 8) & 0xFF)) + (delta1 * ((hex_color2 >> 8) & 0xFF))),
            (uint8_t)(((1 - delta1) * (hex_color1 & 0xFF)) + (delta1 * (hex_color2 & 0xFF)))
        );

        uint32_t color2 = rgb(
            (uint8_t)(((1 - delta2) * ((hex_color1 >> 16) & 0xFF)) + (delta2 * ((hex_color3 >> 16) & 0xFF))),
            (uint8_t)(((1 - delta2) * ((hex_color1 >> 8) & 0xFF)) + (delta2 * ((hex_color3 >> 8) & 0xFF))),
            (uint8_t)(((1 - delta2) * (hex_color1 & 0xFF)) + (delta2 * (hex_color3 & 0xFF)))
        );

        for (int x = minx; x <= maxx; ++x) {
            double t = (x - x1) / (x2 - x1);
            uint32_t final_color = rgb(
                (uint8_t)(((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((color2 >> 16) & 0xFF))),
                (uint8_t)(((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((color2 >> 8) & 0xFF))),
                (uint8_t)(((1 - t) * (color1 & 0xFF)) + (t * (color2 & 0xFF)))
            );

            put_pixel(x, y, final_color);
        }

        x1 += slope1;
        x2 += slope2;
    }

    x1 = vertices[1].x;
    for (int y = vertices[1].y + 1; y <= vertices[2].y; ++y) {
        int minx = (int)ceil(x1);
        int maxx = (int)floor(x2);

        double delta2 = (y - vertices[1].y) / (double)(vertices[2].y - vertices[1].y);

        uint32_t color1 = rgb(
            (uint8_t)(((1 - delta2) * ((hex_color2 >> 16) & 0xFF)) + (delta2 * ((hex_color3 >> 16) & 0xFF))),
            (uint8_t)(((1 - delta2) * ((hex_color2 >> 8) & 0xFF)) + (delta2 * ((hex_color3 >> 8) & 0xFF))),
            (uint8_t)(((1 - delta2) * (hex_color2 & 0xFF)) + (delta2 * (hex_color3 & 0xFF)))
        );

        for (int x = minx; x <= maxx; ++x) {
            double t = (x - x1) / (x2 - x1);
            uint32_t final_color = rgb(
                (uint8_t)(((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((hex_color3 >> 16) & 0xFF))),
                (uint8_t)(((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((hex_color3 >> 8) & 0xFF))),
                (uint8_t)(((1 - t) * (color1 & 0xFF)) + (t * (hex_color3 & 0xFF)))
            );

            put_pixel(x, y, final_color);
        }

        x1 += slope3;
        x2 += slope2;
    }
}
