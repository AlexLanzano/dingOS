print:
	lodsb
	or      %al, %al
	jz      print_end

	mov     $0x0e, %ah
	int     $0x10
	jmp     print

print_end:
	ret

    .macro  print string
	lea		\string, %si
	call	print
    .endm


print_hex:
	pusha
	mov		$3, %si
print_hex_loop:
    mov     %dx, %ax
    lea     hex, %bx
	cmp		$-1, %si
	je		print_hex_exit
	and		$0x000f, %ax
    cmp     $10, %ax
    je     print_hex_alpha
    jmp     print_hex_digit

print_hex_alpha:
    add     $87, %ax
    jmp     print_hex_append

print_hex_digit:
    add     $48, %ax

print_hex_append:
    movb     %al, (%bx, %si)
    dec     %si
    ror     $4, %dx
    jmp     print_hex_loop

print_hex_exit:
    mov     $0, %cx
    mov     %cx, 4(%bx)
    print	hex
	popa
	ret

hex:
	.word	0x0000
	.byte   0x0
