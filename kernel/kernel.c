#include <stdint.h>
#include <stddef.h>

#include "serial/serial.h"
#include "display/vga.h"
#include "display/terminal.h"

void kernel_main(void)
{
    serial_write_string(QEMU_SERIAL_PORT, "Hello from Sinx!\n");
	terminal_initialize();
    serial_write_string(QEMU_SERIAL_PORT, "[Success] Initialized terminal\n");
    disable_cursor();
    serial_write_string(QEMU_SERIAL_PORT, "[Success] Disabled cursor!\n");
	terminal_writestring("Hello, World!\n");
	terminal_writestring("Sinx v0.0.1\n");
}
