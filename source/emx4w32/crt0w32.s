        .file "crt0.s"

        .globl  start
	.globl	__text
	.globl	___syscall
	.globl	__data
	.globl	__heap_base
	.globl	__heap_brk
	.globl	__heap_end
	.globl	__init

	.text

start:
__text:
	push	$__data
	call	__dos_init
	jmp	__init

___syscall:
	call	__dos_syscall
	ret

	.space	6, 0x90

__init: cld
	call	__entry1
	call	__entry2
	call	__startup
	call	_main
	addl	$3*4, %esp
	pushl	%eax
	call	_exit
2:	jmp	2b

	.data

__data:
	.long	__text
	.long	_etext
	.long	__data
	.long	_edata
	.long	_edata
	.long	_end
__heap_base:
	.long	0
__heap_end:
	.long	0
__heap_brk:
	.long	0
	.long	0
        .long   0
	.long	0
	.long	0
	.long	0x02000000
	.long	0
	.long	0
	.byte	0
	.space	63, 0

