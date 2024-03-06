#include <stdint.h>
#include <stddef.h>
#include <printf.h>
#include <string.h>

#include "multiboot/multiboot.h"

#include "serial/serial.h"

void put_pixel32(struct multiboot_info* mb_info, uint64_t x, uint64_t y, uint32_t color) {
  *(uint32_t *)(mb_info->framebuffer_addr + x * (mb_info->framebuffer_bpp >> 3) +
                y * mb_info->framebuffer_pitch) = color;
}

void flush(struct multiboot_info* mb_info, uint8_t r, uint8_t g, uint8_t b) {
  for (uint32_t x = 0; x < mb_info->framebuffer_width; x++) {
    for (uint32_t y = 0; y < mb_info->framebuffer_height; y++) {
      put_pixel32(mb_info, x, y, ((0xFF << 24) | (r << 16) | (g << 8) | b));
    }
  }
}

void main(struct multiboot_info* mb_info)
{
    dprintf("\033c");
    dprintf("Hello from Sinx v0.0.1\n");
    dprintf("Bootloader: %s\n", (char*)mb_info->boot_loader_name);
    dprintf("Screen: %ux%u\n", mb_info->framebuffer_width, mb_info->framebuffer_height);
    flush(mb_info, 255, 255, 255);
}
