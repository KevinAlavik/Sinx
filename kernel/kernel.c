// Standard libc Imports
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Kernel libc Imports
#include <printf.h>
#include <string.h>
#include <kif.h>

// Boot Imports
#include <multiboot/multiboot.h>

// Arch Specific Imports
#include <i383/cpu/cpu.h>
#include <i383/gdt/gdt.h>

// Kernel Driver Imports
#include <drivers/display/framebuffer.h>
#include <drivers/display/vga.h>
#include <drivers/display/nighterm/nighterm.h>
#include <drivers/serial/serial.h>

// Utility Imports
#include <utils/logger.h>

extern int entry(void);

void printf_wrap(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void kernel_entry(struct multiboot_info *mb_info)
{
    dprintf("* Hello from Sinx v0.0.1 (Build date: %s. %s)\n", __DATE__, __TIME__);
    dprintf("* Bootloader: %s\n", (char *)mb_info->boot_loader_name);
    framebuffer_t *fb = framebuffer_initialize(mb_info);
    if (fb == NULL)
    {
        dprintf("! Failed to initialize framebuffer.\n");
        text_mode_warning();
        return;
    }
    dprintf("* Screen Dimensions: %ux%u\n", fb->width, fb->height);

    if (vga_initialize(fb) != 0)
    {
        dprintf("! Failed to initialize VGA\n");
        return;
    }

    if (nighterm_initialize(NULL, (void *)fb->address, (uint64_t)fb->width, (uint64_t)fb->height, (uint64_t)fb->pitch, (uint16_t)fb->bpp, NULL, NULL) != NIGHTERM_SUCCESS)
    {
        dprintf("! Failed to initialize terminal.\n");
        return;
    }

    if (!init_gdt())
    {
        log(FATAL, "FATAL", "Failed to initialize GDT.");
        dprintf("! Failed to initialize GDT.\n");
    }

    entry();
}
