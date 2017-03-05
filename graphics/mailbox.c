#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#include <mailbox.h>
#include <alloc.h>
#include <string.h>

#include <gpio.h>
#include <mem.h>

static uint32_t *mailbox = (uint32_t *)MAILBOX_BASE;
static uint32_t frame_buffer[10] __attribute__((aligned(4)));


uint32_t read_mailbox(mailbox_channel_t channel)
{
    for(;;){
		while((mem_read(MAILBOX_status) & MAILBOX_EMPTY) != 0);

		uint32_t data = mem_read(MAILBOX_read);
		mailbox_channel_t data_channel = data & 0xf;
		if(data_channel == channel)
			return (data >> 4);
	}
}

void write_mailbox(mailbox_channel_t channel, uint32_t data)
{
	data = (data << 4) | channel;

	while((mem_read(MAILBOX_status) & MAILBOX_FULL) != 0){}
	mem_write(MAILBOX_write, data);
	
}

uint32_t* frame_buffer_init(uint32_t width, uint32_t height, uint32_t depth)
{
	frame_buffer[FB_physical_width] = width;
	frame_buffer[FB_physical_height] = height;
	frame_buffer[FB_virtual_width] = width;
	frame_buffer[FB_virtual_height] = height;
	frame_buffer[FB_pitch] = 0;
	frame_buffer[FB_depth] = depth;
	frame_buffer[FB_x_offset] = 0;
	frame_buffer[FB_y_offset] = 0;
	frame_buffer[FB_address] = 0;
	frame_buffer[FB_size] = 0;

	uint32_t value = (uint32_t)frame_buffer + 0x40000000;
	write_mailbox(FRAME_BUFFER, value);
	uint32_t result;
	
	result = read_mailbox(FRAME_BUFFER);
	if(result == 0)
		return frame_buffer;
	else
		return 0;
}
