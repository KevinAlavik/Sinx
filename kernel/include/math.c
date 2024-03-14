#include "math.h"

int abs(int x)
{
    return x < 0 ? -x : x;
}

double sqrt(double x) {
    if (x < 0) return 0; // Undefined for negative numbers
    double guess = x / 2;
    double last_guess = 0;
    while (guess != last_guess) {
        last_guess = guess;
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

double pow(double x, double y) {
    double result = 1.0;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

double sin(double x) {
    x *= M_PI / 180.0;
    return (x - pow(x, 3) / 6 + pow(x, 5) / 120 - pow(x, 7) / 5040);
}

double cos(double x) {
    x *= M_PI / 180.0;
    return (1 - pow(x, 2) / 2 + pow(x, 4) / 24 - pow(x, 6) / 720);
}

double tan(double x) {
    x *= M_PI / 180.0;
    return sin(x) / cos(x);
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

double ceil(double x) {
    int ix = (int)x;
    return ix >= x ? ix : ix + 1;
}

double floor(double x) {
    int ix = (int)x;
    return ix <= x ? ix : ix - 1;
}
