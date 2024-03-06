#include <stdint.h>
#include <stddef.h>
#include <printf.h>
#include <string.h>

#include "serial/serial.h"
#include "display/vga.h"
#include "display/terminal.h"

void kernel_main(void)
{
    dprintf("Hello from Sinx!\n");
	terminal_initialize();
    dprintf("[Success] Initialized terminal\n");
    disable_cursor();
    dprintf("[Success] Disabled cursor!\n");
	printf("Sinx v0.0.1\n");
    printf("--------------------\n");
    printf("Hello, World!\n");
}
