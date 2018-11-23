#include <types.h>
#include <arch/x86/asm.h>
#include <memory/paging.h>

void startc()
{
	return;
	/* uint64_t efer; */
	/* uint64_t *pgmap; */

	/* init_memory_map(e820_map); */

	/* pgmap = init_page_map(0x700000); */
	/* map_range(pgmap, 0x100000, 0xC0000000, 10); */

	/* set_cr3(pgmap); */
	/* enable_pae(); */
    /* enable_long_mode(); */
	/* enable_paging(); */

	/* ljmp(main); */
}
