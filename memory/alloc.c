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
	uint8_t *mem_byte = (uint8_t *)heap_start;
	while((uint32_t)mem_byte < _heap_end){
		block_t *block = (block_t *)mem;

		if(block->free && size <= block->size){

			
			if(b_ptr->size - size > sizeof(block_t)){ // splits the block into two blocks
				uint8_t *mem_temp = mem;
				printf("%x\n", (uint32_t) mem_temp);
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
	
	if(last_alloc+size+sizeof(block_t) < heap_end){ // allocates a block to the end of the heap
		block_t *b_ptr = (block_t*) last_alloc;
		b_ptr->free = 0;
		b_ptr->size = size;

		last_alloc += size;
		last_alloc += sizeof(block_t);

		memset((char*)(uint32_t)b_ptr + sizeof(block_t), 0, size);
		return (char*)(uint32_t)b_ptr + sizeof(block_t);
		    
	}
	return NULL;
	
}

char* realloc(void *block, size_t size)
{
	block_t *block = (block_t *)(mem - sizeof(block_t));

	if((uint32_t)mem == last_alloc || block->size <= size){
		block->size = size;
		return mem;
		    
	}
	block_t *next_block = (block_t *)(mem + block->size);

	size_t next_block_space = sizeof(block_t) + next_block->size;

	if(next_block->free && block->size + next_block_space <= size){
		block->size += next_block_space;
		return mem;
		    
	}

	block->free = 1;
	block_t *new_block = (block_t *)last_alloc;
	new_block->free = 0;
	new_block->size = size;

	last_alloc += size;
	last_alloc += sizeof(block_t);

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
