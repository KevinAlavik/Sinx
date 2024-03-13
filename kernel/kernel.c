#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <printf.h>
#include <string.h>
#include <kif.h>
#include <multiboot/multiboot.h>
#include <i383/cpu/cpu.h>
#include <i383/gdt/gdt.h>
#include <drivers/display/framebuffer.h>
#include <drivers/display/vga.h>
#include <drivers/display/nighterm/nighterm.h>
#include <drivers/serial/serial.h>
#include <utils/logger.h>

extern int entry(void);
struct multiboot_info *mb_info;

void printf_wrap(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

multiboot_module_t* find_module(const char* name) {
    multiboot_module_t* modules = (multiboot_module_t*) mb_info->mods_addr;
    for (int i = 0; i < (int)mb_info->mods_count; i++) {
        const char* module_name = (const char*) modules[i].cmdline;
        if (strcmp(module_name, name) == 0) {
            return &modules[i];
        }
    }
    return NULL;
}

void kernel_entry(struct multiboot_info *mb) {
    mb_info = mb;
    dprintf("* Hello from Sinx v0.0.1 (Build date: %s. %s)\n", __DATE__, __TIME__);
    dprintf("* Bootloader: %s\n", (char *)mb_info->boot_loader_name);
    framebuffer_t *fb = framebuffer_initialize(mb_info);
    if (fb == NULL) {
        dprintf("! Failed to initialize framebuffer.\n");
        text_mode_warning();
        return;
    }
    dprintf("* Screen Dimensions: %ux%u\n", fb->width, fb->height);
    if (vga_initialize(fb) != 0) {
        dprintf("! Failed to initialize VGA\n");
        return;
    }
    if (nighterm_initialize(NULL, (void *)fb->address, (uint64_t)fb->width, (uint64_t)fb->height, (uint64_t)fb->pitch, (uint16_t)fb->bpp, NULL, NULL) != NIGHTERM_SUCCESS) {
        dprintf("! Failed to initialize terminal.\n");
        return;
    }

    dprintf("* Skipping to initialize GDT\n");

    int status = entry();
    printf("%d\n", status);

    uint32_t color1 = rgb(255, 0, 0);
    uint32_t color2 = rgb(0, 255, 0);
    uint32_t color3 = rgb(0, 0, 255);
    draw_triangle_with_gradient(color1, color2, color3);
}
