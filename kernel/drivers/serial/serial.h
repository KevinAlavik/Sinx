#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdint.h>

#define QEMU_SERIAL_PORT 0x3f8

void outb8(uint16_t port, uint8_t value);
void outb16(uint16_t port, uint16_t value);
void outb32(uint16_t port, uint32_t value);
uint8_t inb8(uint16_t port);
uint16_t inb16(uint16_t port);
uint32_t inb32(uint16_t port);
void iowait();
void serial_flush(uint16_t port);

#endif // __SERIAL_H__
