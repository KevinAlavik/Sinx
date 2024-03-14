#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <math.h>
#include <stdint.h>

#include "vga.h"


typedef struct {
    int x;
    int y;
} Point;

void swap_points(Point *a, Point *b);
void draw_line(int x0, int y0, int x1, int y1, uint32_t hex_color);
void draw_figure(Point points[], int num_points);

#endif // __GRAPHICS_H__
