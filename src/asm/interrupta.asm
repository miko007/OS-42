.set IRQ_BASE, 0x20

.section .text

.extern _ZN10interrupts16InterruptManager15HandleInterruptEhj
.global _ZN10interrupts16InterruptManager13IgnoreRequestEv

.macro ExceptionRequest num
.global _ZN10interrupts16InterruptManager16ExceptionRequest\num\()Ev
_ZN10interrupts16InterruptManager16ExceptionRequest\num\()Ev:
	movb $\num, (number)
	jmp int_bottom
.endm

.macro InterruptRequest num
.global _ZN10interrupts16InterruptManager17HandleRequest\num\()Ev
_ZN10interrupts16InterruptManager17HandleRequest\num\()Ev:
	movb $\num + IRQ_BASE, (number)
	jmp int_bottom
.endm

InterruptRequest 0x00
InterruptRequest 0x01

int_bottom:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	pushl %esp
	push (number)
	call _ZN10interrupts16InterruptManager15HandleInterruptEhj
	movl %eax, %esp

	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

_ZN10interrupts16InterruptManager13IgnoreRequestEv:
	iret

.data
	number: .byte 0
