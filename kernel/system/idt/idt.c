#include "idt.h"
#include "isr.h"
#include <string.h>

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void isr0(void);

void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    for (int i = 0; i < 256; ++i)
    {
        idt_set_gate(i, (uint32_t)isr0, 0x08, 0x8E);
    }

    idt_flush((uint32_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}

void idt_flush(uint32_t idt_ptr_address)
{
    asm volatile(
        "lidt (%0)"
        :
        : "r"(idt_ptr_address)
        : "memory");
}
