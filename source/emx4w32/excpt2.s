#
#   excpt1.s - frame exception handlers for Win32 and GNU C
#
#   Copyright (C) 1997
#       Rainer Schnitker, Heeper Str. 283, 33607 Bielefeld
#       email: rainer@mathematik.uni-bielefeld.de
#
#   All rights reserved
#

        .data

        .text

        .align 2,0x90
.globl ___xcpt2_new_handler
___xcpt2_new_handler:
        popl  %edx                       # return address
        popl  %eax                       # frame

        movl  %fs:0, %ecx                # prev record
        movl  %esp,  36(%eax)            # p10 try context
        movl  %edi,  32(%eax)            # p9 try context
        movl  %esi,  28(%eax)            # p8 try context
        movl  %ebx,  24(%eax)            # p7 try context
        movl  %ebp,  20(%eax)            # p6 try context
        movl  $0x00,  8(%eax)            # p3 try context
        movl  $__except_handler2,4(%eax) # p2 handler func
        movl  %ecx, (%eax)               # p1 old record

        movl  %eax, %fs:0                # save record
        xorl  %eax, %eax                 # return 0
        jmp   %edx

        .align 2,0x90
.globl ___xcpt2_set_handler
___xcpt2_set_handler:
        movl  4(%esp), %eax              # handler
        movl  %eax, %fs:0                # set
        movl  8(%eax), %eax              # return context status
        ret

        .align 2,0x90
.globl ___xcpt2_del_handler
___xcpt2_del_handler:
        movl  %fs:0, %eax                # get excpt frame
        movl  (%eax), %ecx               # get prev handler
        movl  %ecx, %fs:0                # set prev handler
        movl  8(%eax), %eax              # return context status
        ret

        .align 2,0x90
.globl ___xcpt2_filter
___xcpt2_filter:
        popl  %eax                       # return address
        popl  %eax                       # filter expression
        ret                              # return to _except_handler

        .align 2,0x90
.globl __exception_test_filter
.globl __exception_term_handler
__exception_test_filter:
__exception_term_handler:
        movl  8(%esp), %ecx              # org ebp
        movl  4(%esp), %edx              # handler

        pushl %ebp
        movl  %ecx, %ebp
        call  %edx
        popl  %ebp

        ret

        .align 2,0x90
.globl __abnormal_termination
__abnormal_termination:
        movl %eax, 4(%esp)
        orl %eax, %eax
        setnz %al
        ret

        .align 2,0x90
.globl ___xcpt2_continue
___xcpt2_continue:
        popl  %eax                       # return address
        ret                              # return to _except_handler

