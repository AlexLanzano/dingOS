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
	mov		$0, %dl
    mov     $0x2, %ah       // Tell bios to read sectors
    mov     $1, %al         // load amount of sectors to be read
    mov     $0, %ch         // load the cylinder
    mov     $2, %cl         // load the sector
    mov     $0, %dh         // load the head
    mov     $0x1000, %bx    // load the kernel at p_addr 0x1000
    int     $0x13
	popa
    ret
