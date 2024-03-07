#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed)) idt_entry_t;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_pointer_t;

typedef struct
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t vector;
    uint32_t err;

    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
    uint32_t ss;
} __attribute__((packed)) int_frame_t;

void load_idt(uint32_t);
void trigger_interupt(uint32_t a);
void set_idt_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);
void init_idt();
void irq_register(uint8_t irq, void *handler);
void irq_deregister(uint8_t irq);

#endif /* IDT_H */