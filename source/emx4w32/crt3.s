# crt3.s
# DLLs without runtime environment

        .text

        .globl  __dos_init
__dos_init:
        ret     $4

        .align  2, 0x90
        .globl  __dos_syscall
__dos_syscall:
        jmp     __dos_syscall

        .data

__win32_app:
        .long   1

        .globl  __cdll_flag
__cdll_flag:    .byte 1
