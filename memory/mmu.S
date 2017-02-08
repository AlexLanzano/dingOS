
	.extern _kernel_end
	
	.global enable_mmu
enable_mmu:
	base 			.req r0
	table_addr		.req r1
	page_attribute	.req r2
	temp_attribute	.req r3

	mov base, #0
	ldr table_addr, =page_table

fill_page_loop:
	mov page_attribute, base
	lsl page_attribute, #20


	mov temp_attribute, #0
	orr temp_attribute, #0b10
	orr temp_attribute, #0b100
	orr temp_attribute, #0b1000

	orr page_attribute, temp_attribute

	str page_attribute, [table_addr]
	add table_addr, table_addr, #4
	cmp base, #4096
	bne fill_page_loop

	mrc p15, 0, r1, c2, c0, 0
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #0x1
	mcr p15, 0, r0, c1, c0, 0
	
page_table:
	.word _kernel_end	
