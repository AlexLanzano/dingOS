#include <stdint.h>

#include <memory.h>

typedef struct{
	int8_t mode;
	int32_t size;
	block *blocks;
	directory *parent;
} directory;
