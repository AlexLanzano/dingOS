#ifndef X86_MEMORY_H
#define X86_MEMORY_H

#include <types.h>

#define PML4(x) ((x >> 39) & 0x1FF)
#define PML3(x) ((x >> 30) & 0x1FF)
#define PML2(x) ((x >> 21) & 0x1FF)
#define PML1(x) ((x >> 12) & 0x1FF)

#define PAGE_SIZE 4096

#define PME_PRESENT_MASK 0x1
#define PME_PAGE_MAP_MASK (0xFFFFFFFF << 12)

#define E820_MEM_AVAIL 1

#define for_each_memory_entry(entry, list, count)  \
    for (entry = list; entry - list < count; entry++)

__attribute__((packed)) struct e820_entry {
    uint64_t base;
    uint64_t length;
    uint32_t type;
    uint32_t extended;
};

struct memory_entry {
    uint64_t base;
    uint64_t length;
};

extern int32_t e820_entry_count;
extern struct e820_entry *e820_map;

void init_memory();
void *alloc_page();
void map_range(uint64_t *page_map, uint64_t phys_base, uint64_t virt_base, uint64_t length);

#endif
