#ifndef __GDT_H__
#define __GDT_H__

#include <stdint.h>

typedef struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();
void gdt_flush(uint32_t);
void gdt_set_gate(int, uint32_t, uint32_t, uint8_t, uint8_t);

#endif /* __GDT_H__ */
