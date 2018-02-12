gdt_start:
gdt_null_descriptor:
    // Null descriptor
    .8byte  0x0

gdt_code_descriptor:
    // Code segment

    .2byte  0xffff      // limit 0:15
    .2byte  0x0000      // base 0:15
    .byte   0x00        // base 16:23
    .byte   0b10011010  // Access Byte
    .byte   0b11001111  // Flags  Limit 16:19
    .byte   0x00        // base 24:31

gdt_data_descriptor:
    // Data Segment

    .2byte  0xffff      // limit 0:15
    .2byte  0x0000      // base 0:15
    .byte   0x00        // base 16:23
    .byte   0b10010010  // Access Byte
    .byte   0b11001111  // Flags  Limit 16:19
    .byte   0x00        // base 24:31

gdt_end:

gdt_pointer:
    .2byte  gdt_end - gdt_start - 1
    .4byte  gdt_start

    .set    code_segment, gdt_code_descriptor - gdt_null_descriptor
    .set    data_segment, gdt_data_descriptor - gdt_null_descriptor

enter_pm:
    cli                     // Disable interrupts

    lgdt    (gdt_pointer)   // Load the GDT Descriptor

    mov     %cr0, %eax      // switch to Protected Mode
    or      $0x1, %eax      //
    mov     %eax, %cr0      //

    ljmp    $code_segment, $protected_mode
