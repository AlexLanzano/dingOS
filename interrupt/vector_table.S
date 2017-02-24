vector_table:
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
	ldr pc, [pc, #24]
_reset_handler:					.word	reset_handler
_undefined_instruction_handler:	.word	undefined_instruction_handler
_software_interrupt_handler:	.word	software_interrupt_handler
_prefetch_abort_handler:		.word	prefetch_abort_handler
_data_abort_handler:			.word	data_abort_handler
_irq_handler:					.word	irq_handler
_fiq_handler:					.word	fiq_handler
	.equ	VT_SIZE, (. - vector_table)



.global fill_vector_able
fill_vector_table:
	mov		r0, #0
	MCR		p15, 0, r0, c12, c0, 0  // Write VBAR. Not sure why I need this
	ldr		r0, =vector_table
	ldr		r1, =0x0
	ldr		r3, =VT_SIZE
fill_loop:
	ldr		r2, [r0], #4
	str		r2, [r1], #4
	cmp		r1, r3
	blt		fill_loop
	mov 	pc, lr 					// return
	
	

	
