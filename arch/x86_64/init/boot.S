    .code16
    .global _start

_start:
    jmp     real_mode
    .include "print.s"
    .include "disk.s"
    .include "pm_switch.s"


real_mode:
    xor     %ax, %ax
    mov     %ax, %ss
    mov     %ax, %ds
    mov     %ax, %es
    mov     %ax, %fs
    mov     %ax, %gs
/*
    mov     $0x8000, %bx
    mov     %bx, %ss
    mov     %ax, %sp
    cld
    */

    mov     $0x9000, %bp
    mov     %bp, %sp

    // Clear Screen
    mov     $0x0600, %ax            // set to clear
    mov     $0x0000, %cx            // from (0, 0)
    mov     $0x184f, %dx            // to (28, 79)
    mov     $0x07, %bh
    int     $0x10

    // Set Cursor to 0,0
    mov     $0x2, %ah           // set cursor position
    mov     $0x0, %bh           // set page number to 0
    mov     $0, %dh           // set row
    mov     $0, %dl           // set column
    int     $0x10

    // Load Kernel into Memory
retry:
	cmp		$5, %ax
	je		abort
	inc		%ax
    call    load_kernel
	jc		retry


    // Enter Protected Mode
    jmp    enter_pm

abort:
    jmp     abort

    .code32
protected_mode:
    mov     $data_segment, %ax
    mov     %ax, %ds
    mov     %ax, %ss
    mov     %ax, %es
    mov     %ax, %fs
    mov     %ax, %gs

    mov     $0x90000, %ebp
    mov     %ebp, %esp

    mov     $0x1000, %esi
    call    print_pm
    hlt

print_pm:
    mov     $0xb8000, %edx

print_pm_loop:
    lodsb
    or      %al, %al
    mov     $0x0f, %ah
    jz      print_pm_end

    mov     %ax, (%edx)

    add     $1, %ebx
    add     $2, %edx
    jmp     print_pm_loop

print_pm_end:
    //popa
    ret


//error_msg0:  .asciz "ERROR: failed to read drive parameters. Aborting..."
//error_msg1:  .asciz "ERROR: failed to load kernel. Aborting..."

    . = _start + 510
    .byte 0x55
    .byte 0xaa
msg:         .asciz "SUCCESS!"


    .skip   512, 0x0
