/ emx_386/getcwd.s (emx+gcc) -- Copyright (c) 1992-1998 by Eberhard Mattes

#include <emx/asm386.h>
#include "syscalls.h"

        .globl  ___getcwd

/ int __getcwd (char *buffer, char drive)

        ALIGN

___getcwd:
        pushl   %esi
        movl    2*4(%esp), %esi         /* buffer */
        movb    3*4(%esp), %dl          /* drive */
        cmpb    $0, %dl
        je      1f
        subb    $0x40, %dl
1:      SYSCALL (0x47)
        popl    %esi
        SET_0
        EPILOGUE (__getcwd)
