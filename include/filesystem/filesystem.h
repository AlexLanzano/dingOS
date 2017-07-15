#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>
#include <stddef.h>

#include <alloc.h>
#include <string.h>

#define FT_DIR  0x1
#define FT_FILE 0x2

#define FILE_OVERWRITE 0x0
#define FILE_APPEND    0x1

typedef struct{
	char *name;
	uint8_t free;
	uint8_t type;
	uint8_t permissions;
	uint16_t child_size;
	uint16_t child_capacity;
	uint16_t data_size;
	uint16_t data_capacity;
	uint8_t *data;
	void *parent;
	void **children;
} file;


void init_fs(uint32_t kernel_end);
file* file_init(const char *name, uint8_t type, uint8_t permissions, file *parent);
void file_free(file *file);
int file_append_child(file *dst_file, file *src_file);
uint8_t* file_read(file *file);
int file_write(file *file, void *data, size_t data_size, uint8_t option);	

	
#endif
