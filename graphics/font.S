	.section 	.data
	.align 		4
	.global 	font
font:
	.incbin 	"font0.bin"



	.section	.text
	.global		check_mem_loc
check_mem_loc:
	push	{lr}
	ldr		r1, =font
	mov		r2, #65
	add		r1, r2, lsl #4

	ldrb	r0,[r1, #3]
	
	pop		{pc}
	
/*
	.section	.text
	.global		draw_char

draw_char:
	// void draw_char(char ch, uint32_t x, uint32_t y, uint8_t color)

	ch			.req	r4
	x			.req	r5
	y			.req	r6
	char_addr	.req	r7
	byte		.req	r8
	line_count	.req	r9
	shift_count .req	r10
	
	push	{lr}

	mov		ch, r0
	mov		x, r1
	mov		y, r2

	ldr		char_addr, =font
	add		char_addr, ch, lsl #4

	mov		line_count, #0
line_loop:
	cmp		line_count,	#16
	bge		line_loop_end

	mov		shift_count, #7
byte_loop:
	cmp		shift_count, #0
	blt		byte_loop_end

	ldrb	byte,[char_addr, line_count]
	add		r0, x, shift_count
	add		r1, y, line_count

	lsr		r11, byte, shift_count
	cmp		r11, #0x1
	moveq	r2, #0x00

	b		draw_pixel
	
	
	sub		shift_count, #1
	b		byte_loop
byte_loop_end:	
	
	add		line_count, #1
	b		line_loop

line_loop_end:	

	
	pop		{pc}

	*/

	.section	.text
	.global		draw_char
draw_char:
	cmp r0,#127
	movhi r0,#0
	movhi r1,#0
	movhi pc,lr

	push {r4, r5, r6,r7,r8, lr}
	x .req r4
	y .req r5
	charAddr .req r6
	mov x,r1
	mov y,r2
	ldr charAddr,=font
	add charAddr, r0,lsl #4

lineLoop$:

	bits .req r7
	bit .req r8
	ldrb bits,[charAddr]
	mov bit,#8

charPixelLoop$:

	subs bit,#1
	blt charPixelLoopEnd$
	lsl bits,#1
	tst bits,#0x100
	beq charPixelLoop$

	add r0,x,bit
	mov r1,y
	bl draw_pixel

	teq bit,#0
	bne charPixelLoop$

charPixelLoopEnd$:
	.unreq bit
	.unreq bits
	add y,#1
	add charAddr,#1
	tst charAddr,#0b1111
	bne lineLoop$

	.unreq x
	.unreq y
	.unreq charAddr

	width .req r0
	height .req r1
	mov width,#8
	mov height,#16
	
	pop	{r4, r5, r6, r7,r8, pc}
	.unreq width
	.unreq height
