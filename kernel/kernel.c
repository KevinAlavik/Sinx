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
#include "arch/cpu/cpu.h"

// Display Imports
#include "drivers/display/framebuffer.h"
#include "drivers/display/vga.h"
#include "drivers/display/nighterm/nighterm.h"

void kernel_entry(struct multiboot_info *mb_info)
{
    printf("Hello from Sinx v0.0.1 (Build date: %s. %s)\n", __DATE__, __TIME__);
    dprintf("Bootloader: %s\n", (char *)mb_info->boot_loader_name);
    framebuffer_t *fb = framebuffer_initialize(mb_info);
    dprintf("Screen Dimensions: %ux%u\n\n", fb->width, fb->height);

    vga_initialize(fb);
    dprintf("Initialized VGA Library\n");

    int n = nighterm_initialize(NULL, (uint32_t*)fb->addr, fb->width, fb->height, fb->pitch, fb->bpp, NULL, NULL);

    if (n != NIGHTERM_SUCCESS)
    {
        dprintf("Failed to initialize terminal.\n");
        return;
    }

    printf("Hello from Sinx v0.0.1 (Build date: %s. %s)\n", __DATE__, __TIME__);
    printf("Bootloader: %s\n", (char *)mb_info->boot_loader_name);
    printf("Screen Dimensions: %ux%u\n\n", fb->width, fb->height);

    if(!nighterm_create_terminal("tty0", NULL, true)) {
        dprintf("Failed to create tty0.\n");
        return;
    }

    printf("Hello tty0!\n");
}
