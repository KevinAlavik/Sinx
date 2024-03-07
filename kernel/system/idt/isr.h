#ifndef __ISR_H__
#define __ISR_H__

#include <stdint.h>

typedef struct
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void isr_handler(registers_t);

#endif // __ISR_H__