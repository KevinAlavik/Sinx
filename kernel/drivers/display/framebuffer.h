#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <stdint.h>
#include <string.h>
#include "../../multiboot/multiboot.h"

typedef struct {
    uint64_t addr;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
} framebuffer_t;

framebuffer_t* framebuffer_initialize(struct multiboot_info* mb_info);
framebuffer_t* request_framebuffer();

#endif // __FRAMEBUFFER_H__
