/*

 dll0.s (emx+gcc) -- Copyright (c) 1992-1996 by Eberhard Mattes

 patched for rsxnt (c) Rainer Schnitker

*/

        .globl  __text
        .globl  ___syscall
        .globl  __data
        .globl  __heap_base
        .globl  __heap_brk
        .globl  __heap_end
        .globl  __init

        .text

__text:
        push    $__data
        call    __dos_init
        jmp     __init


___syscall:
        call    __dos_syscall
        ret

__init: cld
        jmp     __DllEntryPoint

        .data

/*
  The data segment starts with a table containing the start and end
  addresses of the text, data and bss segments
*/

__data:
        .long   __text
        .long   __etext
        .long   __data
        .long   __edata
        .long   __edata
        .long   __end
__heap_base:
        .long   0                       /* heap base address */
__heap_end:
        .long   0                       /* heap end address */
__heap_brk:
        .long   0                       /* heap brk address */
        .long   0                       /* heap offset */
        .long   0                       /* list of OS/2 DLL references */
        .long   0                       /* stack base address */
        .long   0                       /* stack end address */
        .long   0x02000001              /* flags: DLL */
        .long   0                       /* reserved */
        .long   0                       /* reserved */
        .byte   0                       /* options */
        .space  63, 0

        .long   0, 0
