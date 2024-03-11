// Standard libc Imports
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Kernel libc Imports
#include <printf.h>
#include <string.h>

// Boot Imports
#include <multiboot/multiboot.h>

// Arch Specific Imports
#include <i383/cpu.h>

// Kernel Driver Imports
#include <drivers/display/framebuffer.h>
#include <drivers/display/vga.h>
#include <drivers/display/nighterm/nighterm.h>

void kernel_entry(struct multiboot_info *mb_info)
{
    dprintf("* Hello from Sinx v0.0.1 (Build date: %s. %s)\n", __DATE__, __TIME__);
    dprintf("* Bootloader: %s\n", (char *)mb_info->boot_loader_name);
    framebuffer_t *fb = framebuffer_initialize(mb_info);
    if(fb == NULL) {
        dprintf("! Failed to initialize framebuffer.\n");
        return;
    }
    dprintf("- Initialized Framebuffer.\n");
    dprintf("* Screen Dimensions: %ux%u\n", fb->width, fb->height);

    if(vga_initialize(fb) != 0) {
        dprintf("! Failed to initialize VGA\n");
        return;
    }
    dprintf("- Initialized VGA Library\n");

    int n = nighterm_initialize(NULL, (void*)fb->address, (uint64_t)fb->width, (uint64_t)fb->height, (uint64_t)fb->pitch ,(uint16_t)fb->bpp, NULL, NULL);

    if (n != NIGHTERM_SUCCESS)
    {
        dprintf("! Failed to initialize terminal.\n");
        return;
    } else {
        dprintf("- Initialized Terminal.\n");
    }

    printf("Hello from Sinx!\n");
}
