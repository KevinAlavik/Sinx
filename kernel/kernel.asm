section .data
message db "Welcome to Sinx!", 0xA, 0
section .text
extern printf_wrap

global entry

entry:
    push message
    call printf_wrap
    add esp, 4
    ret
