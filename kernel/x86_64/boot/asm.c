#include <types.h>
#include "asm.h"

inline void set_cr3(void *value)
{
    __asm__("mov %0, %%cr3"
            :
            : "a" (value));
}

inline void enable_pae()
{
    __asm__("mov %cr4, %eax\n\t"
            "or $0x20, %eax\n\t"
            "mov %eax, %cr4");
}

inline uint32_t rdmsr(uint32_t msr)
{
    uint32_t eax;
    __asm__("rdmsr"
            :"=a" (eax)
            :"c" (msr));
    return eax;
}

inline void wrmsr(uint32_t msr, uint32_t value)
{
    __asm__("wrmsr"
            :
            : "c" (msr), "a" (value));
}

inline void enable_long_mode()
{
    uint64_t efer;
    efer = rdmsr(MSR_EFER);
    efer |= (1 << 8);
    wrmsr(MSR_EFER, efer);
}

inline void enable_paging()
{
    uint32_t cr0;
    __asm__("mov %%cr0, %0"
            : "=r" (cr0)
            :);
    cr0 |= (1 << 31);
    cr0 |= (1 << 16);
    __asm__("mov %0, %%cr0"
            :
            : "r" (cr0));
}

inline void ljmp(uint16_t seg, uint32_t addr)
{
    struct __attribute__((packed)) {
        uint32_t addr;
        uint16_t seg;
    } kernel_main;

    kernel_main.seg = seg;
    kernel_main.addr = addr;

    __asm__("ljmp *(%%eax)"
            :
            : "a" (&kernel_main));
}
