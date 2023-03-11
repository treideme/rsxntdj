# crt3.s (emx+gcc) -- Copyright (c) 1994 by Eberhard Mattes
#
# This module is used by the following types of executables:
#
# - DLLs without runtime environment

        .globl  __dos_init
        .globl  __dos_syscall
        .globl  __cdll_flag

__dos_init:
        ret     $4

        .align  2, 0x90

__dos_syscall:
        jmp     __dos_syscall

        .data

__cdll_flag:    .byte 1


# rs: add eh_frame
        .globl  ___eh_frame_init
        .globl  ___eh_frame_term

        .text

        .align  2, 0x90
___eh_frame_init:
___eh_frame_term:
        ret
