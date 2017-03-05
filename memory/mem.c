#include <stdint.h>
#include <mem.h>

void mem_write(uint32_t address, uint32_t data)
{
	*(uint32_t *)address = data;
}

uint32_t mem_read(uint32_t address)
{
	return *(uint32_t *)address;
}
