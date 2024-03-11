%define ALIGN       (1 << 0)
%define MEMINFO     (1 << 1)
%define GRAPHICS    (1 << 2)
%define FLAGS       (ALIGN | MEMINFO | GRAPHICS)
%define MAGIC       0x1BADB002
%define CHECKSUM    -(MAGIC + FLAGS)

%define GMODE       0
%define GWIDTH      0
%define GHEIGHT     0
%define GDEPTH      0

section .multiboot
    align 4
header_start:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0, 0, 0, 0, 0
    dd GMODE
    dd GWIDTH
    dd GHEIGHT
    dd GDEPTH
header_end:

section .bss
    align 16
    stack_bottom resb 16384
    stack_top equ $

section .text
    global _start

extern kernel_entry
_start:
    mov esp, stack_top
    push ebx
    cli
    call kernel_entry
    sti
    hlt
    jmp 1b
