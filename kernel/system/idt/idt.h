#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>

typedef struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

typedef struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;


void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void idt_flush(uint32_t);
void isr_handler(registers_t regs);

#endif // __IDT_H__
