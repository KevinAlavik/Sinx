section .text

global isr0
extern isr_handler

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

isr_common_stub:
    pusha
    mov ax, ds
    push ax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler
    pop ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret
