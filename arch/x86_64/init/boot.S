    .code16
    .global _start
    .global main


_start:
    jmp     main
    nop

abort:
    jmp     abort

    .include "boot_sector.S"


    .macro  clear_screen
    mov     $0x0600, %ax            # set to clear
    mov     $0x0000, %cx            # from (0, 0)
    mov     $0x184f, %dx            # to (28, 79)
    mov     $0x07, %bh
    int     $0x10
    .endm

    .macro  cursexy row, col
    mov     $0x2, %ah           # set cursor position
    mov     $0x0, %bh           # set page number to 0
    mov     \row, %dh           # set row
    mov     \col, %dl           # set column
    int     $0x10
    .endm

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


error_0:
    print   error_msg0
    jmp     abort
error_1:
    print   error_msg1
    jmp     abort

max_sector:
    .byte   0
max_cylinder:
    .byte   0
max_head:
    .byte   0

read_drive_parameters:
    pusha
    mov     $0x8, %ah       // Tell bios to read the drive parameters
    mov     $0, %dl         // Select drive 0
    int     $0x13
    mov     %dh, max_head
    mov     %cx, %bx
    and     $0x1f, %cx
    mov     %cx, max_sector
    mov     %bx, %cx
    and     $0xff, %cx
    mov     %cx, max_cylinder
    popa
    ret

load_kernel:
    pusha
    mov     $0x2, %ah       // Tell bios to read sectors
    mov     2, %al          // load amount of sectors to be read
    mov     $0, %ch         // load the cylinder
    mov     $1, %cl         // load the sector
    mov     $0, %dh         // load the head
    mov     $0x9999, %bx
    int     $0x13
    popa
    ret
testtt:
    print   welcome
    jmp abort
main:
    mov     0x8000, %bp
    mov     %bp, %sp
/*
    //clear_screen
    //cursexy $0, $0

    //print   welcome
    cursexy $1, $0

    print   reading
    cursexy $2, $0
    call    read_drive_parameters
    jc      error_0
    */
    mov  $0, %bx
disk_read:
    mov $0, %ah
    int $0x13
  //  print   loading
    //cursexy $3, $0
    cmp     $10, %bx
    je      error_1
    inc     %bx

    call    load_kernel
    jc      disk_read

    lea     0x9000, %ax


welcome:	.asciz "Welcome to DingOS!"
reading:    .asciz "Reading drive parameters..."
loading:    .asciz "Loading the kernel into memory..."
error_msg0:  .asciz "ERROR: failed to read drive parameters. Aborting..."
error_msg1:  .asciz "ERROR: failed to load kernel. Aborting..."
    . = _start + 510
    .byte 0x55
    .byte 0xaa
    .skip 2048, 0xda
