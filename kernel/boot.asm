%define ALIGN       (1 << 0)
%define MEMINFO     (1 << 1)
%define GRAPHICS    (1 << 2)
%define FLAGS       (ALIGN | MEMINFO | GRAPHICS)
%define MAGIC       0x1BADB002
%define CHECKSUM    -(MAGIC + FLAGS)

%define GMODE       0   ; Graphics mode. 0 = graphics, 1 = text
%define GWIDTH      0   ; Width. 0 for default
%define GHEIGHT     0   ; Height. 0 for default
%define GDEPTH      0   ; Depth. 0 for default

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

extern main
_start:
    mov esp, stack_top
    call main
    cli
    hlt
    jmp 1b
