#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdint.h>

#define MAILBOX_BASE 0x3f00b880

#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

typedef enum{
	MBP_SIZE = 0,
	MBP_REQUEST_RESPONSE,
	MBP_DATA
} mailbox_propert_buffer_t;

typedef enum{
	POWER_MANAGEMENT = 0,
	FRAME_BUFFER,
	VIRTUAL_UART,
	VCHIQ,
	LEDS,
	BUTTONS,
	TOUCH_SCREEN,
	RESERVED,
	P_TAGS_ARM2VC,
	P_TAGS_VC2ARM
} mailbox_channel_t;

typedef enum{
	MAILBOX_read = MAILBOX_BASE,
	MAILBOX_peek = MAILBOX_BASE + 0x10,
	MAILBOX_sender = MAILBOX_BASE + 0x14,
	MAILBOX_status = MAILBOX_BASE + 0x18,
	MAILBOX_config = MAILBOX_BASE + 0x1c,
	MAILBOX_write = MAILBOX_BASE + 0x20
} mailbox_register_offset;

typedef enum{
	FB_physical_width = 0,
	FB_physical_height,
	FB_virtual_width,
	FB_virtual_height,
	FB_pitch,
	FB_depth,
	FB_x_offset,
	FB_y_offset,
	FB_address,
	FB_size
} mailbox_framebuffer_t;

uint32_t read_mailbox(mailbox_channel_t channel);
void write_mailbox(mailbox_channel_t channel, uint32_t data);
uint32_t* frame_buffer_init(uint32_t width, uint32_t height, uint32_t depth);

#endif
