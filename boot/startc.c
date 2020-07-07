#include <types.h>
#include "memory.h"
#include "asm.h"

#define KERNEL_MAIN_PHYS 0x87a4
#define KERNEL_MAIN_VIRT 0xc0100000 + KERNEL_MAIN_PHYS

void startc()
{
	uint64_t *page_map;

    init_memory();
    page_map = alloc_page();

    /* Map bootloader and kernel */
    map_range(page_map, 0x0, 0x0, 12);
    map_range(page_map, 0x0, 0xc0100000, 12);

    /* Map VGA Framebuffer */
    map_range(page_map, 0xB8000, 0xB8000, 8);

	set_cr3(page_map);
	enable_pae();
    enable_long_mode();
	enable_paging();
	ljmp(0x18, KERNEL_MAIN_VIRT);
}
