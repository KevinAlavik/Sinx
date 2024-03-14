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
    int i, j;
    int ymin = INT_MAX, ymax = INT_MIN;

    for (i = 0; i < num_points; i++) {
        if (points[i].y < ymin)
            ymin = points[i].y;
        if (points[i].y > ymax)
            ymax = points[i].y;
    }

    for (int y = ymin; y <= ymax; y++) {
        int intersection_points = 0;
        int intersections[100];
        for (i = 0, j = num_points - 1; i < num_points; j = i++) {
            if ((points[i].y < y && points[j].y >= y) || (points[j].y < y && points[i].y >= y)) {
                int x_intersect = (points[i].x + (y - points[i].y) / (double)(points[j].y - points[i].y) * (points[j].x - points[i].x));
                intersections[intersection_points++] = x_intersect;
            }
        }

        for (i = 0; i < intersection_points - 1; i++) {
            for (j = 0; j < intersection_points - i - 1; j++) {
                if (intersections[j] > intersections[j + 1]) {
                    int temp = intersections[j];
                    intersections[j] = intersections[j + 1];
                    intersections[j + 1] = temp;
                }
            }
        }

        for (i = 0; i < intersection_points; i += 2) {
            draw_line(intersections[i], y, intersections[i + 1], y, rgb(255, 255, 255));
        }
    }
}
