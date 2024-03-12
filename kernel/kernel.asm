section .data
message db "Hello from Sinx!", 0xA, 0
section .text
extern printf_wrap

global entry

entry:
    push message
    call printf_wrap
    add esp, 4
    ret
