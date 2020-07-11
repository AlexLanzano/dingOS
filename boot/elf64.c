#include <types.h>
#include <string.h>
#include "memory.h"
#include "elf64.h"

elf64_header_t *elf_find_header()
{
    elf64_header_t *header = NULL;
    uint8_t *data;
    for (data = (uint8_t *)0x8000; (uint32_t)data < 0x9000; data++) {
        if (data[0] != 0x7f || data[1] != 'E' || data[2] != 'L' || data[3] != 'F') {
            continue;
        }

        header = (elf64_header_t *)data;
    }

    return header;
}

int invalid_elf_header(elf64_header_t *elf_header)
{
    if (elf_header->ident[0] != 0x7f ||
        elf_header->ident[1] != 'E' ||
        elf_header->ident[2] != 'L' ||
        elf_header->ident[3] != 'F') { // Redundant check if this is actually an elf header
            return 1;
    }
    
    if (elf_header->ident[4] != 2) { // not 64 bit
        return 1;
    }

    if (elf_header->ident[5] != 1) { // not little endian
        return 1;
    }

    return 0;
}

uint64_t elf_load(uint64_t *page_map, elf64_header_t *elf_header)
{
    elf64_prog_header_t *prog_header;
    uint8_t *data;
    uint32_t kernel_phys_start = 0x10000;
    
    if (invalid_elf_header(elf_header)) {
        // TODO: print an error here
        return 1;
    }

    prog_header = (elf64_prog_header_t *)((uint8_t *)elf_header + elf_header->phoff);

    data = (uint8_t *)elf_header + prog_header[0].offset;

    memcpy((uint8_t *)kernel_phys_start, data, prog_header[0].filesz);
    memset((uint8_t *)((uint32_t *)kernel_phys_start+prog_header[0].filesz), 0, prog_header[0].memsz-prog_header[0].filesz);
    
    map_range(page_map, 0x10000, prog_header[0].vaddr, 1);
    
    return prog_header[0].vaddr;
}
