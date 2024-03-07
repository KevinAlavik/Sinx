#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>
#include <printf.h>
#include <stddef.h>

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_pointer_t;

typedef struct {
    uint32_t r15;
    uint32_t r14;
    uint32_t r13;
    uint32_t r12;
    uint32_t r11;
    uint32_t r10;
    uint32_t r9;
    uint32_t r8;
    uint32_t rbp;
    uint32_t rdi;
    uint32_t rsi;
    uint32_t rdx;
    uint32_t rcx;
    uint32_t rbx;
    uint32_t rax;

    uint32_t vector;
    uint32_t err;

    uint32_t rip;
    uint32_t cs;
    uint32_t rflags;
    uint32_t rsp;
    uint32_t ss;
} __attribute__((packed)) int_frame_t;

void load_idt(uint32_t);
void trigger_interrupt(uint32_t);
void set_idt_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);
void init_idt();
void irq_register(uint8_t irq, void* handler);
void irq_deregister(uint8_t irq);

#endif /* __IDT_H__ */
