#include <stdint.h>
#include <stddef.h>
#include <printf.h>
#include <string.h>

#include "multiboot/multiboot.h"

#include "serial/serial.h"

void main(struct multiboot_info* mb_info)
{
	dprintf("\033c");
	dprintf("Hello from Sinx v0.0.1\n");
	dprintf("Bootloader: %s\n", (char*)mb_info->boot_loader_name);
	dprintf("%ux%u\n", mb_info->framebuffer_width, mb_info->framebuffer_height);
}
