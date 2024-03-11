#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>
#include <printf.h>

#include <drivers/serial/serial.h>

void hcf();
void hlt();
void a20_enable();

#endif // __CPU_H__
