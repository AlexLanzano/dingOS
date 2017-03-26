	.section	.data
	.align		4
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


	.section	.data
release_buffer:
	.int	release_buffer_end - release_buffer
	.int	0
	.int	0x48001	// Tag ID
	.int	0		// buffer length
	.int	0		// request/response
	.int	0		// null tag
release_buffer_end:

	.section	.data
alloc_frame_buffer:
	.int	alloc_frame_buffer_end - alloc_frame_buffer
	.int	0

	.int	0x48003
	.int	8
	.int	0
	.int	1360
	.int	768

	.int	0x48004
	.int	8
	.int	0
	.int	1360
	.int	768

	.int	0x48005
	.int	4
	.int	0
	.int	24

	.int	0x40001
	.int	8
	.int	0
	.int	0
	.int	0

	.int	0
alloc_frame_buffer_end:	
	
	.section .text
	.global frame_buffer_init
frame_buffer_init:

	push	{r4, lr}
/*
	mov		r0, #8
	ldr		r1, =release_buffer
	add		r1, #0xc0000000
	bl		mailbox_write

	mov		r0, #8
	ldr		r1, =alloc_frame_buffer
	add		r1, #0xc0000000
	bl		mailbox_write
*/	
	width				.req	r0
	height				.req	r1
	depth				.req	r2
	frame_buffer_addr	.req	r4

	
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
