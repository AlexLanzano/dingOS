

enter_lm:
	// Initializing Long Mode

	// Setup Page Tables
	mov		$pdpt, %eax
	orl		$0b11, %eax
	mov		%eax, (pml4)

	mov		$pd, %eax
	orl		$0b11, %eax
	mov		%eax, (pdpt)

	mov		$0x10000, %eax
	orl		$0b11, %eax
	mov		%eax, (pd)

	mov		$0, %ecx
fill_pt_loop:
	mov		$0x1000, %eax
	mul		%ecx
	orl		$0b11, %eax
	mov		%eax, 0x10000(,%ecx,8)



	// Enable Physical Address extensions
	mov		%cr4, %eax
	or		$0b100000, %eax
	mov		%eax, %cr4

	.align	4096
pml4:
	.skip	4096
pdpt:
	.skip	4096
pd:
	.skip	4096
pt:
	.skip	4096
