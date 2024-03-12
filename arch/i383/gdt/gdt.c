#include "gdt.h"

struct GDT gdt;

extern void reloadSegments(void);

struct GDT_Entry gdt_entry(uint32_t base, uint16_t limit, uint8_t access, uint8_t flags)
{
    struct GDT_Entry entry;
    entry.base_low = base & 0xFFFF;
    entry.base_mid = (base >> 16) & 0xFF;
    entry.base_high = (base >> 24) & 0xFF;
    entry.limit_low = limit & 0xFFFF;
    entry.limit_flags = (limit >> 16) & 0x0F;
    entry.limit_flags |= flags << 8;
    entry.access = access;
    return entry;
}

int init_gdt()
{
    a20_enable();
    gdt.null_descriptor = gdt_entry(0, 0x0000, 0x00, 0x0);
    gdt.kernel_code_segment = gdt_entry(0, (uint16_t)0xFFFFF, 0x9A, 0xC);
    gdt.kernel_data_segment = gdt_entry(0, (uint16_t)0xFFFFF, 0x92, 0xC);
    gdt.user_code_segment = gdt_entry(0, (uint16_t)0xFFFFF, 0xFA, 0xC);
    gdt.user_data_segment = gdt_entry(0, (uint16_t)0xFFFFF, 0xF2, 0xC);
    gdt.task_state_segment = gdt_entry(0, 0x0, 0x89, 0x0);

    struct
    {
        uint16_t limit;
        void *base;
    } __attribute__((packed)) gdtr;

    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = &gdt;

    if (gdtr.base == NULL)
    {
        dprintf("! Failed to initialize GDT. Base of gdtr (pointer to GDT) is NULL?\n");
        return 1;
    }

    asm volatile("lgdt %0" : : "m"(gdtr));
    reloadSegments();
    return 0;
}
