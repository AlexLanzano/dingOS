
	.equ	I_BIT, 0x80
	.equ	F_BIT, 0x40
	.equ	USR_MODE, 0x10
	.equ	FIQ_MODE, 0x11
	.equ	IRQ_MODE, 0x12
	.equ	SVC_MODE, 0x13
	.equ	ABT_MODE, 0x17
	.equ	UND_MODE, 0x1b
	.equ	SYS_MODE, 0x1f


	.equ	stack_top, 0x10000000

	.equ	fiq_stack_top, stack_top - 0x1000
	.equ	irq_stack_top, stack_top - 0x2000
	.equ	abt_stack_top, stack_top - 0x3000
	.equ	und_stack_top, stack_top - 0x4000
	.equ	mon_stack_top, stack_top - 0x5000
	.equ	svc_stack_top, stack_top - 0x6000
	.equ	sys_stack_top, stack_top - 0x7000
	
	.section ".text.boot"
	
	.global _start
	.global _enable_interrupts

	.extern _kernel_end
	
_start:
	
	msr		CPSR_c, #FIQ_MODE|I_BIT|F_BIT
	ldr		sp, =fiq_stack_top

	msr		CPSR_c, #IRQ_MODE|I_BIT|F_BIT
	ldr		sp, =irq_stack_top

	msr		CPSR_c, #ABT_MODE|I_BIT|F_BIT
	ldr		sp, =abt_stack_top

	msr		CPSR_c, #UND_MODE|I_BIT|F_BIT
	ldr		sp, =und_stack_top

	msr		CPSR_c, #SYS_MODE|I_BIT|F_BIT
	ldr		sp, =sys_stack_top

	msr		CPSR_c, #SVC_MODE|I_BIT|F_BIT
	ldr		sp, =svc_stack_top
	
	bl		fill_vector_table

	mov		sp, #0x8000
	bl		_cstart
	
_inf_loop:
	b _inf_loop

_enable_interrupts:
	mrs     r0, cpsr
	bic     r0, r0, #0x80
	msr     cpsr_c, r0
	mov     pc, lr
