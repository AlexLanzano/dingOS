#include <types.h>

#define PAGE_SIZE 4096
#define PML4(x) ((x >> 39) & 0x1FF)
#define PML3(x) ((x >> 30) & 0x1FF)
#define PML2(x) ((x >> 21) & 0x1FF)
#define PML1(x) ((x >> 12) & 0x1FF)

#define ENTRY_PRESENT_MASK 0b1
#define ENTRY_PAGE_MAP_MASK (0xFFFFFFFF << 12)

#define E820_MEM_AVAIL 1
struct e820_entry {
    uint64_t base;
    uint64_t length;
    uint32_t type;
    uint32_t extended;
};

extern int32_t e820_entry_count;
extern struct e820_entry *e820_map;

void *alloc_page()
{
    struct e820_entry *entry;
    for (entry = e820_map; entry - e820_map < e820_entry_count; entry++) {
        if (entry->type != E820_MEM_AVAIL) {
            continue;
        }

        if (entry->length >= PAGE_SIZE) {
            return (void *)(uint32_t) entry->base;
        }
    }
    return NULL;
}

int page_entry_present(uint64_t *page_map_entry)
{
    return *page_map_entry & ENTRY_PRESENT_MASK;
}

void *get_page_map(uint64_t *page_map_entry)
{
    return (void *)(uint32_t) ((*page_map_entry >> 12) & ENTRY_PAGE_MAP_MASK);
}

void set_page_map(uint64_t *page_map_entry, uint64_t *page_map)
{
    *page_map_entry = ((ENTRY_PAGE_MAP_MASK) & (*page_map << 12)) | 0b11;
}

uint64_t *page_map_walk(uint64_t *page_map, uint64_t offset)
{
    uint64_t *page_map_ret;
    uint64_t *page_map_entry = page_map + offset;

    if (!page_entry_present(page_map_entry)) {
        page_map_ret = alloc_page(); // TODO: add error handling
        set_page_map(page_map_entry, page_map_ret);
    } else {
        page_map_ret = get_page_map(page_map_entry);
    }

    return page_map_ret;
}

void map_page(uint64_t *page_map, uint64_t phys_addr, uint64_t virt_addr)
{
    uint64_t *pml3 = page_map_walk(page_map, PML4(virt_addr));
    uint64_t *pml2 = page_map_walk(pml3, PML3(virt_addr));
    uint64_t *pml1 = page_map_walk(pml2, PML2(virt_addr));
    uint64_t *page_frame = page_map_walk(pml1, PML1(virt_addr));

    uint64_t *page = page_frame + (virt_addr & 0xFFF);
    *page = phys_addr;
}

void map_range(uint64_t *page_map, uint64_t phys_base, uint64_t virt_base, uint64_t length)
{
    for (uint64_t i = 0; i < length; i++) {
        uint64_t phys_addr = phys_base + (PAGE_SIZE * i);
        uint64_t virt_addr = virt_base + (PAGE_SIZE * i);
        map_page(page_map, phys_addr, virt_addr);
    }
}

void startc()
{
	uint64_t *page_map = alloc_page();

    // map kernel
    map_range(page_map, 0x7c00, 0x7c00, 10);

	/* set_cr3(pgmap); */
	/* enable_pae(); */
    /* enable_long_mode(); */
	/* enable_paging(); */

	/* ljmp(main); */
}
