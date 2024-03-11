#include "logger.h"

#include <drivers/display/nighterm/nighterm.h>
#include <printf.h>
#include <stdarg.h>

void log(enum LogLevel level, char* tag, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    switch (level) {
        case OK:
            nighterm_set_fg_color(123, 255, 66);
            printf("[%s] ", tag);
            nighterm_set_fg_color(255, 255, 255);
            break;
        case WARNING:
            nighterm_set_fg_color(255, 165, 0);
            printf("[%s] ", tag);
            nighterm_set_fg_color(255, 255, 255);
            break;
        case ERROR:
            nighterm_set_fg_color(255, 0, 0);
            printf("[%s] ", tag);
            nighterm_set_fg_color(255, 255, 255);
            break;
        case FATAL:
            nighterm_set_fg_color(128, 0, 128);
            printf("[%s] ", tag);
            nighterm_set_fg_color(255, 255, 255);
            break;
        case DEBUG:
            nighterm_set_fg_color(0, 0, 255);
            printf("[%s] ", tag);
            nighterm_set_fg_color(255, 255, 255);
            break;
        case INFO:
            nighterm_set_fg_color(0, 128, 128);
            printf("[%s] ", tag);
            nighterm_set_fg_color(255, 255, 255);
            break;
        default:
            nighterm_set_fg_color(255, 255, 255);
            printf("[%s] ", tag);
            break;
    }

    vprintf(fmt, args);
    printf("\n");

    va_end(args);
}
