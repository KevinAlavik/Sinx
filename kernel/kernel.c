#include <stdint.h>
#include <stddef.h>
#include <printf.h>
#include <string.h>

#include "serial/serial.h"
#include "display/vga.h"
#include "display/terminal.h"

void kernel_main(void)
{
	terminal_initialize();
    printf("Hello, World!");
}
