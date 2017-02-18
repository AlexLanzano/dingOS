#include <string.h>
#include <alloc.h>


uint32_t _heap_start = 0;
uint32_t _heap_end = 0;
uint32_t _last_alloc = 0;
uint32_t _mem_total = 0;

void mm_init(uint32_t base_addr)
{
	_last_alloc = base_addr + 0x1000;
	_heap_start = _last_alloc;
	_heap_end = 0x20000000;
	memset((char *)_heap_start, 0, _heap_end - _heap_start);
}

void show_blocks()
{
	uint32_t *heap = (uint32_t *)_heap_start;
	uint32_t block_number = 0;
	while((uint32_t) heap < _heap_end){
		block_t *block = (block_t *)heap;
		//printf("BLOCK %i: size = %i free = %i", block->size, block->free);
		block += block->size;
		block += sizeof(block_t);
	}
	
}

void* malloc(size_t size)
{
	uint8_t *mem = (uint8_t *)_heap_start;

	// checks to see if there is a free block large enough already made
	while((uint32_t)mem < _heap_end){
		block_t *b_ptr = (block_t *)mem;

		if(b_ptr->free && size <= b_ptr->size){

			
			if(b_ptr->size - size > sizeof(block_t)){
				// if the block is large enough to be split
				uint8_t *mem_temp = mem;
				mem_temp += sizeof(block_t);
				mem_temp += size;

				block_t *split_block = (block_t*) mem_temp;

				split_block->size = b_ptr->size - sizeof(block_t) - size;
				split_block->free = 1;

				b_ptr->size = size;
				            
			}

			b_ptr->free = 0;
			return (char*)(mem + sizeof(block_t));
			        
		}
		mem += b_ptr->size;
		mem += sizeof(block_t);
		
	}
	// If no blocks were found, then it creates a new one at the end of the heap
	if(_last_alloc+size+sizeof(block_t) < _heap_end){ 
		block_t *b_ptr = (block_t*) _last_alloc;
		b_ptr->free = 0;
		b_ptr->size = size;

		_last_alloc += size;
		_last_alloc += sizeof(block_t);

		memset((char*)(uint32_t)b_ptr + sizeof(block_t), 0, size);
		return (char*)(uint32_t)b_ptr + sizeof(block_t);
		    
	}
	
	return NULL;
	
}

char* realloc(void *mem, size_t size)
{
	block_t *block = (block_t *)(mem - sizeof(block_t));

	// if block is at the end of heap, extend the block
	if((uint32_t)mem == _last_alloc || block->size <= size){
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
	block_t *new_block = (block_t *)_last_alloc;
	new_block->free = 0;
	new_block->size = size;

	_last_alloc += size;
	_last_alloc += sizeof(block_t);

	//possibly need to memset new_block + sizeof(block_t) to 0
	memcpy(new_block + sizeof(block_t), mem, size);
	return (char *)(uint32_t) new_block + sizeof(block_t);
	
}

void free(void *block)
{
	block_t *b_ptr = block - sizeof(block_t);
	b_ptr->free = 1;
	memset(block, 0, b_ptr->size);
}
