#ifndef __GDT_H__
#define __GDT_H__

#include <stdint.h>
#include <printf.h>
#include <i383/cpu/cpu.h>

struct GDT_Entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_flags;
    uint8_t base_high;
} __attribute__((packed));

struct GDT
{
    struct GDT_Entry null_descriptor;
    struct GDT_Entry kernel_code_segment;
    struct GDT_Entry kernel_data_segment;
    struct GDT_Entry user_code_segment;
    struct GDT_Entry user_data_segment;
    struct GDT_Entry task_state_segment;
} __attribute__((packed));

struct GDT_Entry gdt_entry(uint32_t base, uint16_t limit, uint8_t access, uint8_t flags);
int init_gdt();

#endif // __GDT_H__