	.section	.text
	.global		write32
write32:
	// void write32(uint32_t addr, uint32_t value)
	str		r1, [r0]
	bx		lr

	.global		read32
read32:
	// uint32_t read32(uint32_t addr)
	ldr		r0, [r0]
	bx		lr

	.global dummy
dummy:
	bx		lr
