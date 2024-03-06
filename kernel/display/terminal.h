#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stdint.h>
#include <string.h>

#include "../serial/serial.h"
#include "vga.h"

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_writestring(const char *data);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();

#endif // __TERMINAL_H__
