gdt64_start:
gdt64_null_descriptor:
    // Null descriptor
    .8byte  0x0

gdt64_code_descriptor:
    // Code segment

    .2byte  0xffff      // limit 0:15
    .2byte  0x0000      // base 0:15
    .byte   0x00        // base 16:23
    .byte   0b10011010  // Access Byte
    .byte   0b00101111  // Flags  Limit 16:19
    .byte   0x00        // base 24:31


gdt64_end:

gdt64_pointer:
    .2byte  gdt64_end - gdt64_start - 1
    .4byte  gdt64_start

    .set    code64_segment, gdt64_code_descriptor - gdt64_null_descriptor


enter_lm:
	// Initializing Long Mode

	// Setup Page Tables
    // map 0x100000 to 0xC0000000

    // map plm4 entry
	mov		$0x701000, %eax
	orl		$0b11, %eax
	mov		%eax, 0x700000

    // map pdpt entry
	mov		$0x702000, %eax
	orl		$0b11, %eax
	mov		%eax, 0x701000

    // map pdpt entry (higher half)
	mov		$0x702000, %eax
	orl		$0b11, %eax
	mov		%eax, 0x701018

    // map pd entry
	mov		$0x703000, %eax
	orl		$0b11, %eax
	mov		%eax, 0x702000

    // map pt entries
	mov		$0, %ecx
	mov		$0x0, %eax
	orl		$0b11, %eax
fill_pt_loop:
	mov		%eax, 0x703000(,%ecx,8)
    add     $0x1000, %eax
    inc     %ecx
    cmp     $1024, %ecx
    jne     fill_pt_loop

    // set cr3 to plm4
    movl    $0x700000, %eax
    movl    %eax, %cr3

	// Enable Physical Address extensions
	mov		%cr4, %eax
	or		$0b100000, %eax
	mov		%eax, %cr4

    // Set long mode bit in EFER MSR
    mov     $0xc0000080, %ecx
    rdmsr
    orl     $1 << 8, %eax
    wrmsr

    // enable paging
    movl    %cr0, %eax
    orl     $1 << 31, %eax
    mov     %eax, %cr0

    // Setup gdt64
    lgdt    (gdt64_pointer)
    ljmp    $code64_segment, $0x100000
    hlt
