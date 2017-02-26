#ifndef MEMORY_IO_H
#define MEMORY_IO_H

#define read(type, address) \
	*(type *)address		\

#define write(type, address, data)				\
	*(type *)address = data;					\

#endif
