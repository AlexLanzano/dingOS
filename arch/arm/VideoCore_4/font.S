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




	.section	.text
	.global		draw_char
draw_char:
	cmp r1,#127
	movhi r1,#0
	movhi r2,#0
	movhi pc,lr

	push {r4, r5, r6,r7,r8, lr}
	x .req r5
	y .req r6
	color .req r3
	charAddr .req r7
	mov x,r2
	mov y,r3
	ldr charAddr,=font
	add charAddr, r1,lsl #4

lineLoop$:

	bits .req r8
	bit .req r9
	ldrb bits,[charAddr]
	mov bit,#8

charPixelLoop$:

	subs bit,#1
	blt charPixelLoopEnd$
	lsl bits,#1
	tst bits,#0x100
	beq charPixelLoop$

	add r1,x,bit
	mov r2,y
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
