// Standard libc Imports
#include <stdint.h>
#include <stddef.h>

// Kernel libc Imports
#include <printf.h>
#include <string.h>

// Boot Imports
#include "multiboot/multiboot.h"

// System Imports
#include "system/gdt.h"

// Display Imports
#include "drivers/display/framebuffer.h"
#include "drivers/display/vga.h"

void kernel_entry(struct multiboot_info* mb_info)
{
    dprintf("\033c");
    dprintf("Hello from Sinx v0.0.1\n");
    dprintf("Bootloader: %s\n", (char*)mb_info->boot_loader_name);

    framebuffer_t* fb = framebuffer_initialize(mb_info);
    dprintf("Screen Dimensions: %ux%u\n\n", fb->width, fb->height);

    vga_initialize(fb);
    dprintf("Initialized VGA Library\n");

    gdt_init();
    dprintf("Initialized GDT\n");
}
