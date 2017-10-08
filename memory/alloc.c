#include <string.h>
#include <alloc.h>


mm_handler_t mm_handler;


void mm_init(uint32_t *base_addr)
{
	mm_handler.last_alloc = base_addr;
	mm_handler.heap_start = base_addr;
	mm_handler.heap_end = (uint32_t *)0x28000;
	mm_handler.bytes_allocated = 0;
	mm_handler.total_blocks = 0;
}

/*
void show_blocks()
{
	uint32_t *heap = (uint32_t *)_heap_start;
	uint32_t block_number = 0;
	while ((uint32_t) heap < _heap_end){
		block_t *block = (block_t *)heap;
		//printf("BLOCK %i: size = %i free = %i", block->size, block->free);
		block += block->size;
		block += sizeof(block_t);
	}

}
*/

block_t *_next_block(block_t *block)
{
	uint8_t *ret = (uint8_t*)block;
	ret += sizeof(block_t);
	ret += block->size;
	return (block_t*)ret;
}

uint8_t *_create_block(uint32_t size)
{
	block_t *b_ptr = (block_t*)mm_handler.last_alloc;
	b_ptr->free = 0;
	b_ptr->size = size;
	mm_handler.last_alloc = (uint32_t *)_next_block(b_ptr);

	return (uint8_t*)(b_ptr + sizeof(block_t));
}

uint8_t *_split_block(uint8_t *block_addr, uint32_t size)
{
	block_t *b_ptr;
	uint32_t split_mem_size;
	uint8_t *return_addr;

	b_ptr = (block_t*)block_addr;
	split_mem_size = b_ptr->size - size;
	b_ptr->size = size;
	b_ptr->free = 0;
	return_addr = (uint8_t*)(b_ptr + sizeof(block_t));
	b_ptr = _next_block(b_ptr);
	b_ptr->free = 1;
	b_ptr->size = split_mem_size - sizeof(block_t);

	return return_addr;
}

void* malloc(size_t size)
{
	block_t *b_ptr = (block_t*)mm_handler.heap_start;
	uint32_t block_count = 0;

	// checks to see if there is a free block large enough already made
	while (block_count < mm_handler.total_blocks) {
		if (b_ptr->free && size <= b_ptr->size) {
			if (b_ptr->size - size > sizeof(block_t)) {
				// if the block is large enough to be split
				return _split_block((uint8_t*)b_ptr, size);
			}
		}
		b_ptr = _next_block(b_ptr);
		++block_count;
	}
	// If no blocks were found, then it creates a new one at the end of the heap
	if (mm_handler.last_alloc + size + sizeof(block_t) < mm_handler.heap_end){
		return _create_block(size);
	}

	return NULL;
}

char* realloc(void *mem, size_t size)
{
	block_t *block = (block_t *)(mem - sizeof(block_t));

	// if block is at the end of heap, extend the block
	if((uint32_t *)mem == mm_handler.last_alloc || block->size <= size){
		block->size = size;
		return mem;
	}

	block_t *next_block = (block_t *)(mem + block->size);
	size_t next_block_space = sizeof(block_t) + next_block->size;

	// if the next block is free and is large enough, then combine the blocks
	if(next_block->free && block->size + next_block_space <= size){
		block->size += next_block_space;
		return mem;
	}

	// creates a new block at the end of heap
	block->free = 1;
	block_t *new_block = (block_t *)mm_handler.last_alloc;
	new_block->free = 0;
	new_block->size = size;
	mm_handler.last_alloc += size;
	mm_handler.last_alloc += sizeof(block_t);

	//possibly need to memset new_block + sizeof(block_t) to 0
	memcpy(new_block + sizeof(block_t), mem, size);
	return (char *)((uint32_t*) new_block + sizeof(block_t));

}

void free(void *block)
{
	block_t *b_ptr = block - sizeof(block_t);
	b_ptr->free = 1;
	memset(block, 0, b_ptr->size);
}
