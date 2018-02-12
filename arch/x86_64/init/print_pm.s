
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
    ret
