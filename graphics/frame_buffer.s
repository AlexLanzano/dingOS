	.section	.data
	.align		4
	.global frame_buffer
frame_buffer:
	.int	1024	// width
	.int	768		// height
	.int	1024	// virtual width
	.int	768		// virtual height
	.int	0		// pitch
	.int	16		// depth
	.int	0		// x offset
	.int	0		// y offset
	.int	0		// address	
	.int	0		// size


	.section .text
	.global frame_buffer_init
frame_buffer_init:
	width				.req	r0
	height				.req	r1
	depth				.req	r2
	frame_buffer_addr	.req	r4

	push	{r4, lr}
	ldr		frame_buffer_addr, =frame_buffer
	
	str		width, [r4, #0]
	str		height, [r4, #4]
	str		width, [r4, #8]
	str		height, [r4, #12]
	str		depth, [r4, #20]

	.unreq	width
	.unreq	height
	.unreq	depth

	mov 	r0, #1
	mov		r1, frame_buffer_addr
	add		r1, #0xc0000000
	bl		mailbox_write

	mov 	r0, #1
	bl 		mailbox_read

	teq		r0, #0
	movne	r0, #0
	popne	{r4, pc}

	mov		r0, frame_buffer_addr
	pop		{r4, pc}
	.unreq	frame_buffer_addr

	.global get_pitch
get_pitch:
	push	{lr}
	ldr		r1, =frame_buffer
	ldr		r0, [r1, #16]
	pop		{pc}
	
	.global get_frame_buffer
get_frame_buffer:

	push	{lr}
	ldr		r1, =frame_buffer
	ldr		r0, [r1, #32]
	and		r0, #0x3fffffff
	pop		{pc}
