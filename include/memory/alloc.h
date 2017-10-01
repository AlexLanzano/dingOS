#ifndef ALLOC_H
#define ALLOC_H

#include <stdint.h>

typedef struct{
	uint32_t *heap_start;
	uint32_t *heap_end;
	uint32_t *last_alloc;
	uint32_t bytes_allocated;
	uint32_t total_blocks;
} mm_handler_t;

typedef struct{
	uint8_t free;
	size_t size;
} block_t;

void mm_init(uint32_t *base_addr);
void* malloc(size_t size);
char* realloc(void *block, size_t size);
void free(void *block);

#endif
