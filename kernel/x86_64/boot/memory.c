#include <types.h>
#include "memory.h"

int32_t available_memory_count;
struct memory_entry *available_memory = (struct memory_entry *)0x20000;

int32_t reserved_memory_count = 2;
struct memory_entry reserved_memory[] = {
    {0x0, 0x1000},
    {0x7c00, 0x10000}
};

void init_memory()
{
    struct e820_entry *entry;
    struct memory_entry available_entry;

    available_memory_count = 0;
    for (entry = e820_map; entry - e820_map < e820_entry_count; entry++) {
        if (entry->type != E820_MEM_AVAIL) {
            continue;
        }

        available_entry.base = entry->base;
        available_entry.length = entry->length;
        available_memory[available_memory_count++] = available_entry;
    }
}

uint32_t entry_intersect( struct memory_entry *e1,  struct memory_entry *e2)
{
    uint64_t a1 = e1->base;
    uint64_t a2 = e1->base + e1->length;

    uint64_t b1 = e2->base;
    uint64_t b2 = e2->base + e2->length;

    if (a2 < b1 || b2 < a1) {
        return 0;
    }
    return 1;
}

void *alloc_page()
{
    struct memory_entry *entry;
    struct memory_entry *reserved;
    struct memory_entry page;

    page.length = PAGE_SIZE;

    for_each_memory_entry(entry, available_memory, available_memory_count) {
        /* Check if the memory we want to allocate is overlaping with reserved memory*/
        for_each_memory_entry(reserved, reserved_memory, reserved_memory_count) {
            page.base = entry->base;
            if (!entry_intersect(&page, reserved)) {
                continue;
            }

            if (reserved->base + reserved->length >= entry->base +entry->length) {
                    entry->base += entry->length;
                    entry->length = 0;
            } else {
                    entry->length -= (reserved->base + reserved->length) - entry->base;
                    entry->base = reserved->base + reserved->length;
            }
        }

        if (PAGE_SIZE > entry->length) {
            continue;
        }

        entry->base += PAGE_SIZE;
        entry->length -= PAGE_SIZE;

        return (void *)(uint32_t) page.base;
    }

    return NULL;
}

int pme_present(uint64_t *page_map_entry)
{
    return *page_map_entry & PME_PRESENT_MASK;
}

void *pme_get_page_map(uint64_t *page_map_entry)
{
    return (void *)(uint32_t) ((*page_map_entry) & PME_PAGE_MAP_MASK);
}

void pme_set_page_map(uint64_t *page_map_entry, uint64_t *page_map)
{
    *page_map_entry = ((PME_PAGE_MAP_MASK) & ((uint32_t)page_map)) | 0b11;
}

void pme_set_page(uint64_t *page_map_entry, uint64_t page)
{
    *page_map_entry = ((PME_PAGE_MAP_MASK) & (page)) | 0b11;
}

uint64_t *page_map_walk(uint64_t *page_map, uint64_t offset)
{
    uint64_t *page_map_ret;
    uint64_t *page_map_entry = page_map + offset;

    if (!pme_present(page_map_entry)) {
        page_map_ret = alloc_page(); /* TODO: Handle error */
        pme_set_page_map(page_map_entry, page_map_ret);
    } else {
        page_map_ret = pme_get_page_map(page_map_entry);
    }

    return page_map_ret;
}

void map_page(uint64_t *pml4, uint64_t phys_addr, uint64_t virt_addr)
{
    uint64_t *pml3 = page_map_walk(pml4, PML4(virt_addr));
    uint64_t *pml2 = page_map_walk(pml3, PML3(virt_addr));
    uint64_t *pml1 = page_map_walk(pml2, PML2(virt_addr));

    uint64_t *pml1_entry = pml1 + PML1(virt_addr);
    pme_set_page(pml1_entry, phys_addr);
}

void map_range(uint64_t *page_map, uint64_t phys_base, uint64_t virt_base, uint64_t length)
{
    for (uint64_t i = 0; i < length; i++) {
        uint64_t phys_addr = phys_base + (PAGE_SIZE * i);
        uint64_t virt_addr = virt_base + (PAGE_SIZE * i);
        map_page(page_map, phys_addr, virt_addr);
    }
}
