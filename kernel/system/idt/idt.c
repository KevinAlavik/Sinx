#include "idt.h"

#define IDT_ENTRIES 256

idt_entry_t idt[IDT_ENTRIES];
idt_pointer_t idt_p;
void *irq_handlers[16];

extern uint32_t isr_tbl[];

static const char *exception_strings[32] = {
    "Division By Zero", "Debug", "Nonmaskable Interrupt", "Breakpoint",
    "Overflow", "Bound Range Exceeded", "Invalid Opcode",
    "Device Not Available", "Double Fault", "Coprocessor Segment Overrun",
    "Invalid TSS", "Segment Not Present", "Stack Segment Fault",
    "General Protection Fault", "Page Fault", "Reserved", "x87 FPU Error",
    "Alignment Check", "Machine Check", "Simd Exception",
    "Virtualization Exception", "Control Protection Exception", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Hypervisor Injection Exception", "VMM Communication Exception",
    "Security Exception", "Reserved"};

extern void load_idt(uint32_t);

void set_idt_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    dprintf("[IDT] Setting IDT gate for interrupt %d. Base: 0x%08X, Sel: 0x%04X, Flags: 0x%02X\n",
            num, base, sel, flags);
    idt[num].offset_low = (base & 0xFFFF);
    idt[num].selector = sel;
    idt[num].ist = 0;
    idt[num].flags = flags;
    idt[num].offset_middle = (base >> 16) & 0xFFFF;
    idt[num].offset_high = (base >> 32) & 0xFFFFFFFF;
    idt[num].zero = 0;
}

void init_idt() {
    dprintf("[IDT] Initializing IDT\n");
    idt_p.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
    idt_p.base = (uint32_t)&idt;

    for (size_t i = 0; i < 16; i++) {
        irq_handlers[i] = NULL;
    }

    for (int i = 0; i < IDT_ENTRIES; ++i) {
        set_idt_gate(i, isr_tbl[i], 0x08, 0x8E);
    }

    load_idt((uint32_t)&idt_p);
    dprintf("[IDT] IDT Initialization complete\n");
}

void excp_handler(int_frame_t *frame) {
    if (frame->vector < 0x20) {
        dprintf("[IDT] Exception: %s\n", exception_strings[frame->vector]);
    } else if (frame->vector >= 0x20 && frame->vector <= 0x2f) {
        int irq = frame->vector - 0x20;
        void (*handler)(int_frame_t *);
        handler = irq_handlers[irq];

        if (handler != NULL) {
            handler(frame);
        }
    } else if (frame->vector == 0x80) {
        dprintf("[IDT] Handling system call\n");
    }
}

void irq_register(uint8_t irq, void *handler) {
    dprintf("[IDT] Registering IRQ handler for IRQ %d\n", irq);
    irq_handlers[irq] = handler;
}

void irq_deregister(uint8_t irq) {
    dprintf("[IDT] Deregistering IRQ handler for IRQ %d\n", irq);
    irq_handlers[irq] = NULL;
}
