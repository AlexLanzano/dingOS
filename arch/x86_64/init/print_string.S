print_string:
	lodsb
	or %al, %al
	jz print_string_end

	mov $0x0e, %ah
	int $0x10
	jmp print_string

print_string_end:
	ret

	.macro print_string string
	lea		string, %si
	call	print_string
	.endm
