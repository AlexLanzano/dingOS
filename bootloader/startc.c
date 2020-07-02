#include <types.h>
#include "memory.h"
#include "asm.h"

#define KERNEL_MAIN 0x8784

void startc()
{
	uint64_t *page_map;

    init_memory();
    page_map = alloc_page();

    /* Map bootloader and kernel */
    map_range(page_map, 0x0, 0x0, 512);

    /* Map VGA Framebuffer */
    map_range(page_map, 0xB8000, 0xB8000, 8);

	set_cr3(page_map);
	enable_pae();
    enable_long_mode();
	enable_paging();
	ljmp(0x18, KERNEL_MAIN);
}
