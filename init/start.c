#include <stdint.h>

extern int _bss_start;
extern int _bss_end;

extern void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags);

void _cstart(uint32_t r0, uint32_t r1, uint32_t r2)
{
	int *bss = &_bss_start;
	int *bss_end = &_bss_end;

	while(bss< bss_end)
		*bss++ = 0;

	kernel_main(r0, r1, r2);

	while(1){}
		
}
