#ifndef X86_ASM_H
#define X86_ASM_H

#include <types.h>

#define MSR_EFER 0xC0000080

void set_cr3(void *value);
void enable_pae();
uint32_t rdmsr(uint32_t msr);
void wrmsr(uint32_t msr, uint32_t value);
void enable_long_mode();
void enable_paging();
void load_gdt(uint32_t addr);
void ljmp(uint16_t seg, uint32_t addr);

#endif
