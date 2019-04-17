    .code16
    .global _start
_start:
    xor     %ax, %ax
    mov     %ax, %ss
    mov     %ax, %ds
    mov     %ax, %fs
    mov     %ax, %gs
    mov     %ax, %es

    // Save disk id
    mov     %dl, diskid

    // Setup stack
    mov     $_start, %sp

    // Establish memory map
    xor     %ebx, %ebx              // Clear ebx
    mov     e820_map, %di           // Set map address to 0xE820
    mov     $0, %eax                // Set entires to 0
    push    %eax
e820:
    mov     $0x534D4150, %edx       // Set magic number
    mov     $24, %ecx               // Return 24 byte entries
    mov     $0xe820, %eax           // Set interupt function number
    int     $0x15
    cmp     $0x534D4150, %eax       // Check if call failed
    je      e820_1
e820_fail:
    hlt
e820_1:
    pop     %eax                    // Increase entry counter
    inc     %eax
    push    %eax
    test    %ebx, %ebx              // Check if done
    jz      e820_finish
    add     $24, %di                // Increment address for next entry
    jmp     e820
e820_finish:
    mov     %eax, e820_entry_count  // Store the amount of entries

    // Read kernel from disk into memory
    mov     $0x42, %ah              // Use extended read function
    mov     diskid, %dl             // Set disk id
    mov     $dap, %si               // Set pointer to dap
    int     $0x13

    // Enter Protected mode
    cli

    lgdt    (gdt_pointer)

    mov     %cr0, %eax
    or      $0x1, %eax
    mov     %eax, %cr0

    ljmp    $0x8, $protected_mode

fail:
    cli
    hlt

    .code32
protected_mode:
    movw    $data_segment, %ax
    movw    %ax, %ss
    movw    %ax, %ds
    movw    %ax, %fs
    movw    %ax, %gs
    movw    %ax, %es
    movl    $_start, %esp
    call    startc
    hlt

// Disk Address Packet
dap:
    .byte   0x10                // Size of dap
    .byte   0x0                 // Unused
    .2byte  0x9                 // Number of Sectors to be read
    .2byte  0x7e00              // Offset
    .2byte  0x0                 // Segment
    .8byte  0x1                 // Start sector

diskid:
    .byte

// TODO: use macros to make this look nicer
gdt_start:
gdt_null_descriptor:
    .8byte  0x0

gdt_code_descriptor:
    .2byte  0xffff
    .2byte  0x0000
    .byte   0x00
    .byte   0b10011010
    .byte   0b11001111
    .byte   0x00

gdt_data_descriptor:
    .2byte  0xffff
    .2byte  0x0000
    .byte   0x00
    .byte   0b10010010
    .byte   0b11001111
    .byte   0x00

gdt64_code_descriptor:
    .2byte  0xffff
    .2byte  0x0000
    .byte   0x00
    .byte   0b10011010
    .byte   0b11101111
    .byte   0x00

gdt_end:

    .global gdt_pointer
gdt_pointer:
    .2byte  gdt_end - gdt_start - 1
    .4byte  gdt_start

    .set    code_segment, gdt_code_descriptor - gdt_null_descriptor
    .set    data_segment, gdt_data_descriptor - gdt_null_descriptor

    .global e820_map
e820_map:
    .long 0x6000

    .global e820_entry_count
e820_entry_count:
    .long

    .org 0x1fe
    .byte   0x55, 0xaa
