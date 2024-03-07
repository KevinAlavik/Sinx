#include "isr.h"
#include "idt.h"
#include <printf.h>

void isr_handler(registers_t regs)
{
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
