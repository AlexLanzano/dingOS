	# tries to read sector with address AX in to buffer at ES:BX
read_disk:
    push 	%ax					# Store address
	push	%cx					# Store the amount of tries
	push	%bx					# Store buffer offset

	# sector = (addr % sectors_per_track) + 1
	mov	 	track_size, %bx		# Store sectors per track in BX
	xor 	%dx, %dx			# 0 out dx
	div		%bx					# divide DX:AX by BX.
								# AX = Quotient
								# DX = Remainder
	inc		%dx
	mov		%dl, %cl			# Store sector in CL

	# cylinder = (addr / sectors_per_track) / head_count
	mov		head_count, %bx		# Store number of heads in BX
	xor		%dx, %dx
	div		%bx					# Divide DX:AX by BX
								# AX = Quotient
								# DX = Remainder
	mov		%al, %ch			# Store the cylinder in CH

	# head = (addr / sectors_per_tack) % head_count
	mov		%dl, %dh			# Store the number of heads in DH

	mov		$0x0201, %ax		# Use subfunction 2, read 1 sector
	mov		boot_drive, %dl		# Starting from boot_drive
	pop		%bx					# Restore buffer offset
	int		$0x13
	jc		read_disk_fail		# Failed to read

	pop 	%cx					# Discard try count
	pop		%ax					# Discard address
	ret

read_disk_fail:
	pop		%cx					# Get try count
	inc		%cx
	cmp  	$4, %cx    			# stop after 3 tries
	je		boot_fail

	# Reset disc
	xor 	%ax, %ax
	int		$0x13

	pop 	%ax					# Get address
	jmp		read_disk


read_file:
    ## Steps:
    ## get root directory size
    ## get root directory address
    ## read each sector
    ## scan the sector to see if it contains the file


    mov     $32, %ax
    xor     dx, dx
    mul     root_size
    div     sector_size
