.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set GRAPHICS, 1<<2
.set FLAGS,    ALIGN | MEMINFO | GRAPHICS
.set MAGIC,    0x1BADB002
.set CHECKSUM, - (MAGIC + FLAGS)

.set GMODE, 0
.set GWIDTH, 0
.set GHEIGHT, 0
.set GDEPTH, 0

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0,0,0,0,0
.long GMODE
.long GWIDTH
.long GHEIGHT
.long GDEPTH

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp
    call main
    cli
1:    hlt
    jmp 1b

.size _start, . - _start
