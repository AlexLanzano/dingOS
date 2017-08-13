#include <stdint.h>
#include <stddef.h>

#include <alloc.h>
#include <filesystem.h>


file **files;
int files_size = 0;

void init_fs()
{
	files = malloc(sizeof(file*) * 20);
	files[0] = malloc(sizeof(file));
	files[0]->free = 0;
	files[0]->type = FT_DIR;
	files[0]->child_size = 0;
	files[0]->child_capacity = 4;
	files[0]->parent = NULL;
	files[0]->children = malloc(sizeof(file*) * 4);
	++files_size;
}

file* file_init(const char *name, uint8_t type, uint8_t permissions, file *parent)
{
	file *new_file = malloc(sizeof(file));
	new_file->name = malloc(sizeof(char)*16);
	strncpy(new_file->name, name, 15);
	new_file->type = type;
	new_file->permissions = permissions;
	if(type == FT_DIR){
		new_file->child_size = 0;
		new_file->child_capacity = 4;
		new_file->children = malloc(sizeof(file*) * 4);
	}
	if(type == FT_FILE){
		new_file->data_size = 0;
		new_file->data_capacity = 4096;
		new_file->data = malloc(4096);
	}

	for(int i = 0; i < files_size; ++i){
		if(files[i]->free == 1){
			files[i] = new_file;
			++files_size;
		}
	}
	
	file_append_child(parent, new_file);
	return new_file;
}


void file_free(file *file)
{
	for(int i = 0; i < file->child_size; ++i)
		free(file->children[i]);
	free(file->children);
	free(file->data);
	file->free = 1;
}

int file_append_child(file *dst_file, file *src_file)
{
	if(dst_file->child_size == dst_file->child_capacity)
		return 1;
	// add name check
	dst_file->children[dst_file->child_size++] = src_file;
	return 0;
}

uint8_t* file_read(file *file)
{
	return file->data;
}

int file_write(file *file, void *data, size_t data_size, uint8_t option)
{
	// ADD BOUNDS CHECK
	
	for(uint32_t i = 0; i < data_size; ++i){
		uint8_t d = *(uint8_t*)data++;
		if(option == FILE_OVERWRITE)
			file->data[i] = d;
		if(option == FILE_APPEND)
			file->data[file->data_size+i] = d;
    }

	if(option == FILE_OVERWRITE){
		if(data_size > file->data_size)
			file->data_size = data_size;
	}
	if(option == FILE_APPEND)
		file->data_size += data_size;
		
	return 0;
}
