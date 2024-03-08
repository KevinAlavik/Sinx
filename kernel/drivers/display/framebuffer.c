#include "framebuffer.h"


framebuffer_t fb;

framebuffer_t* framebuffer_initialize(struct multiboot_info* mb_info) {
    fb.address = (void *)(uintptr_t)(uint32_t)mb_info->framebuffer_addr;
    fb.width = mb_info->framebuffer_width;
    fb.height = mb_info->framebuffer_height;
    fb.bpp = mb_info->framebuffer_bpp;
    fb.pitch = mb_info->framebuffer_pitch;
    return &fb;
}

framebuffer_t* request_framebuffer() {
    return &fb;
}
