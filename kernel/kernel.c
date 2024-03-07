// Standard libc Imports
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Kernel libc Imports
#include <printf.h>
#include <string.h>

// Boot Imports
#include "multiboot/multiboot.h"

// System Imports
#include "system/gdt/gdt.h"
#include "system/idt/idt.h"

// Display Imports
#include "drivers/display/framebuffer.h"
#include "drivers/display/vga.h"
#include "drivers/display/nighterm/nighterm.h"

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

    init_idt();

    int n = nighterm_initialize(NULL, fb->addr, fb->width, fb->height, fb->pitch, fb->bpp, NULL, NULL);

    if(n != NIGHTERM_SUCCESS) {
        dprintf("Failed to initialize tty.");
        return;
    }

    printf("Hello from Sinx v0.0.1\n");
    printf("Bootloader: %s\n", (char*)mb_info->boot_loader_name);
    printf("Screen Dimensions: %ux%u\n\n", fb->width, fb->height);
    printf("%s\n", __FILE__);
    printf("(Check serial for startup log)\n");

    int a = 0 / 0;
}
