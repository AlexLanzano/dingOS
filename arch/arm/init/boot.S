
	
	.section ".text.boot"
	
	.global _start

	.extern _kernel_end
	
_start:

	ldr		pc, reset_vector
	ldr		pc, undefined_instruction_vector
	ldr		pc, software_interrupt_vector
	ldr		pc, prefetch_abort_vector
	ldr		pc, data_abort_vector
	ldr		pc, unused_vector
	ldr		pc, irq_vector
	ldr		pc, fast_irq_vector

reset_vector:					.word	reset
undefined_instruction_vector:	.word	undefined_instruction_handler 
software_interrupt_vector:		.word	software_interrupt_handler
prefetch_abort_vector:			.word	prefetch_abort_handler
data_abort_vector:						.word	data_abort_handler
unused_vector:					.word	unused_handler
irq_vector:						.word	irq_handler
fast_irq_vector:				.word	fast_irq_handler

reset:
	mov     r0, #0x8000
    mov     r1, #0x0000
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
	
	mov		sp, #0x8000
	bl		_cstart
	
_inf_loop:
	b _inf_loop
