#include "idt.h"
#include <string.h>
#include <printf.h>

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void isr_handler(registers_t regs) {
    printf("Received interrupt:\n");
    printf("\tds: 0x%X\n", regs.ds);
    printf("\tedi: 0x%X\n", regs.edi);
    printf("\tesi: 0x%X\n", regs.esi);
    printf("\tebp: 0x%X\n", regs.ebp);
    printf("\tesp: 0x%X\n", regs.esp);
    printf("\tebx: 0x%X\n", regs.ebx);
    printf("\tedx: 0x%X\n", regs.edx);
    printf("\tecx: 0x%X\n", regs.ecx);
    printf("\teax: 0x%X\n", regs.eax);
    printf("\tint_no: 0x%X\n", regs.int_no);
    printf("\terr_code: 0x%X\n", regs.err_code);
    printf("\teip: 0x%X\n", regs.eip);
    printf("\tcs: 0x%X\n", regs.cs);
    printf("\teflags: 0x%X\n", regs.eflags);
    printf("\tuseresp: 0x%X\n", regs.useresp);
    printf("\tss: 0x%X\n", regs.ss);
}

void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

    for (int i = 0; i < 256; ++i) {
        idt_set_gate(i, (uint32_t)isr_handler, 0x08, 0x8E);
    }

    idt_flush((uint32_t)&idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags;
}

void idt_flush(uint32_t idt_ptr_address) {
    asm volatile (
        "lidt (%0)"
        :
        : "r"(idt_ptr_address)
        : "memory"
    );
}

