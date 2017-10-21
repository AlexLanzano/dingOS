    .code16
    .text

    .global main

_start:
    jmp main
    nop
    .include "boot_sector.S"
    .include "print_string.S"
    .include "disk.S"


boot_fail:
    print_string string

main:
    print_string string

string:	.asciz "Hello"
error:  .asciz "failed"
    . = _start + 510
    .byte 0x55
    .byte 0xaa
