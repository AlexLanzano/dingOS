#include <stdint.h>


#include <filesystem.h>



void init_fs(uint32_t kernel_end)
{
	
}

file* file_init(uint8_t type, uint8_t permissions, file *parent)
{
	
}

int file_append_child(file *dst_file, file *src_file)
{
	
}

void file_free(file *file)
{
	
}

block* file_data_init(file *file)
{
	
}

void file_data_free(file *file)
{
	
}

int file__expand_children(file *file)
{
	
}
