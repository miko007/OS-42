.set IRQ_BASE, 0x20

.section .text

.extern _ZN10interrupts16InterruptManager15HandleInterruptEhj

.macro ExceptionRequest num
.global _ZN10interrupts16InterruptManager16ExceptionRequestEv
_ZN10interrupts16InterruptManager16ExceptionRequestEv:
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
	#add %esp, 6
	movl %eax, %esp

	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa

.global _ZN10interrupts16InterruptManager13IgnoreRequestEv
_ZN10interrupts16InterruptManager13IgnoreRequestEv:

	iret

.data
	number: .byte 0
