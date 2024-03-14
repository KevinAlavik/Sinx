#include "graphics.h"

void swap_points(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t hex_color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        put_pixel(x0, y0, hex_color);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


void draw_figure(Point points[], int num_points) {
    for (int i = 0; i < num_points - 1; i++) {
        draw_line(points[i].x, points[i].y, points[i+1].x, points[i+1].y, rgb(255, 255, 255));
    }

    draw_line(points[num_points - 1].x, points[num_points - 1].y, points[0].x, points[0].y, rgb(255, 255, 255));
}
