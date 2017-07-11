ENTRY(_start)
MEMORY
{
	ram (W) : ORIGIN = 0x8000, LENGTH = 164K
}


SECTIONS
{
    /* Starts at LOADER_ADDR. */
	. = 0x8000;
	_kernel_start = .;
	_text_start = .;
	.text :
	{
		KEEP(*(.text.boot))
		*(.text)
										    
	} > ram
    . = ALIGN(4096); /* align to page size */
	 _text_end = .;

    _rodata_start = .;
	.rodata :
	{
		*(.rodata)
					    
	} > ram
    . = ALIGN(4096); /* align to page size */
	 _rodata_end = .;

    _data_start = .;
	.data :
	{
		*(.data)
					    
	} > ram
    . = ALIGN(4096); /* align to page size */
	_data_end = .;

    _bss_start = .;
	.bss :
	{
		bss = .;
		*(.bss)
							    
	} > ram
    . = ALIGN(4096); /* align to page size */
	_bss_end = .;
	_kernel_end = .;
			
}
