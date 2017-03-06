	.global	get_mailbox_base
get_mailbox_base:
	ldr		r0, =0x3f00b880
	mov		pc, lr


	.global mailbox_write
mailbox_write:
	// void mailbox_write(uint8_t channel, uint32_t value)
	mailbox		.req	r0
	value		.req	r1
	channel		.req	r2
	status		.req	r3

	mov		channel, r0
	
	push	{lr}
	bl		get_mailbox_base

mailbox_full:
	ldr		status, [mailbox, #0x18]
	tst		status, #0x80000000
	bne		mailbox_full
	
	add		value, channel
	str		value, [mailbox, #0x20]

	.unreq	mailbox
	.unreq	channel
	.unreq	value
	.unreq	status
	
	pop		{pc}
	


	.global mailbox_read
mailbox_read:
	//	uint32_t mailbox_read(uint8_t channel)
	mailbox		.req	r0
	channel		.req	r1
	status		.req	r2
	value		.req	r3

	mov 	r1, r0
	push	{lr}
	bl		get_mailbox_base
	
loop1:
	
mailbox_empty:
	ldr		status, [mailbox, #0x18]		
	tst		status, #0x40000000
	bne		mailbox_empty

	ldr		value, [mailbox, #0x0]
	and		r4, value, #0xf
	teq		r4, channel
	bne		loop1


	and		r0, value, #0xfffffff0

	.unreq	mailbox
	.unreq	channel
	.unreq	status
	.unreq	value

	pop		{pc}

	
