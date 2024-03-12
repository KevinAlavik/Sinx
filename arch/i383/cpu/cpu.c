#include "cpu.h"

void hcf()
{
    asm("cli");
    for (;;)
    {
        asm("hlt");
    }
}

void hlt()
{
    for (;;)
    {
        asm("hlt");
    }
}

void a20_enable()
{
    uint8_t i = inb8(0x92);
    i ^= (1 << 6);
    outb8(0x92, i);
}
