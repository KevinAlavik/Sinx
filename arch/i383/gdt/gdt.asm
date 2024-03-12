global reloadSegments

section .text
reloadSegments:
    jmp 0x08:complete_flush

complete_flush:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax