	.section ".text.boot"

	.global _start
IMPORT _kernel_end

_start:
	ldr sp, =0x8000

	b _cstart


_inf_loop:
	b _inf_loop
