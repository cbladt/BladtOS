global _start
extern _init
extern _fini
extern KernelInit
extern KernelMain

MAGIC_NUMBER 	equ 0x1BADB002
FLAGS		equ 0x0
CHECKSUM	equ -MAGIC_NUMBER
KERNEL_STACK_SIZE	equ 4096

section .bss
align 4

kernel_stack:
	resb KERNEL_STACK_SIZE

section .text
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM


_start:
	mov esp, kernel_stack + KERNEL_STACK_SIZE
	call KernelInit		
	call _init
	call KernelMain	
	call _fini
.loop:
	jmp .loop
