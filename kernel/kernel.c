#include <stdint.h>
#include <stddef.h>

// Serial stuff. TODO: Move this to its own file.
#define QEMU_SERIAL_PORT 0x3f8
#define UNUSED 0x80

void outb8(uint16_t port, uint8_t value);
void outb16(uint16_t port, uint16_t value);
void outb32(uint16_t port, uint32_t value);
uint8_t inb8(uint16_t port);
uint16_t inb16(uint16_t port);
uint32_t inb32(uint16_t port);
void iowait();
void serial_write_string(uint16_t port, const char* data);

void iowait() {
    outb8(UNUSED, 0);
}

void outb8(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

void outb16(uint16_t port, uint16_t value) {
    __asm__ volatile("outw %1, %0" : : "dN"(port), "a"(value));
}

void outb32(uint16_t port, uint32_t value) {
    __asm__ volatile("outl %1, %0" : : "dN"(port), "a"(value));
}

uint8_t inb8(uint16_t port) {
    uint8_t r;
    __asm__ volatile("inb %1, %0" : "=a"(r) : "dN"(port));
    return r;
}

uint16_t inb16(uint16_t port) {
    uint16_t r;
    __asm__ volatile("inw %1, %0" : "=a"(r) : "dN"(port));
    return r;
}

uint32_t inb32(uint16_t port) {
    uint32_t r;
    __asm__ volatile("inl %1, %0" : "=a"(r) : "dN"(port));
    return r;
}

void serial_write_string(uint16_t port, const char* data) {
    while (*data != '\0') {
        outb8(port, *data++);
    }
}

// VGA stuff. TODO: Move this to its own files
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | (bg << 4);
}

static inline uint16_t vga_entry(char uc, uint8_t color) {
    return (uint16_t)uc | ((uint16_t)color << 8);
}

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    } else {
        terminal_buffer[terminal_row * VGA_WIDTH + terminal_column++] = vga_entry(c, terminal_color);
        if (terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row = 0;
            }
        }
    }
}

void terminal_writestring(const char *data) {
    size_t len = strlen(data);
    for (size_t i = 0; i < len; i++) {
        terminal_putchar(data[i]);
    }
}

void kernel_main(void)
{
	terminal_initialize();
	terminal_writestring("Hello, World!\n");
	terminal_writestring("Sinx v0.0.1\n");

    serial_write_string(QEMU_SERIAL_PORT, "Hello from Sinx!\n");
}
