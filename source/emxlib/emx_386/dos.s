.data
        __win32_app:
        .long   0

        __dummy_address:
        .long   0

.text

        .align  2, 0x90
        .globl  __dos_init
__dos_init:
        movl    $__text, %eax
        cmpl    $0x10000, %eax
        je      1f
        cmpl    $0x1000, %eax
        je      1f
        movl    %eax, __win32_app

__rsxnt_init:
        jmp     *__dummy_address
1:      ret     $4

        .align  2, 0x90
        .globl  __dos_syscall
__dos_syscall:
        cmpl    $0, __win32_app
        je      1f
__rsxnt_call:
        jmp     *__dummy_address
1:      int     $0x21
        ret

# add syscall import entries for RSXNT.DLL

.stabs "__ImpNT_RSXNT_Call=RSXNT.dll", 36, 0, 1, __rsxnt_call+2
.stabs "__ImpNT_RSXNT_Init=RSXNT.dll", 36, 0, 2, __rsxnt_init+2
