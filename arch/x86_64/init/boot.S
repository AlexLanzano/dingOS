    .code16
    .text

    .global main

_start:
    jmp main
    nop

    .include "boot_sector.S"

clear_screen:
    pusha
    mov     $0x0600, %ax            # set to clear
    mov     $0x0000, %cx            # from (0, 0)
    mov     $0x184f, %dx            # to (28, 79)
    mov     $0x07, %bh
    int     $0x10
    popa
    ret

reset_cursor:
    pusha
    mov     $0x2, %ah           # set cursor position
    mov     $0x0, %bh           # set page number to 0
    mov     $0x0, %dx           # set colomn and row to 0
    int     $0x10
    popa
    ret


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
	lea		string, %si
	call	print
    .endm



boot_fail:
    print   error

main:
    call    clear_screen
    call    reset_cursor

    print   string

string:	.asciz "Welcome to DingOS!"
error:  .asciz "failed"
    . = _start + 510
    .byte 0x55
    .byte 0xaa
