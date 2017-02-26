#include <stdarg.h>
#include <stdint.h>

#include <mailbox.h>
static mailbox_t mailbox = (mailbox_t *)MAILBOX_BASE;
static uint32_t mbp_buffer[8192] __attribute__((aligned(16)));
static uint32_t mbp_index = 0;


void mailbox_property_init(void)
{
	mbp_buffer[MBP_SIZE] = 16;
	mbp_buffer[MBP_REQUEST_RESPONSE] = 0;
	mbp_index = MBP_DATA;
	mbp_buffer[mbp_index] = 0;
}

void mailbox_property_add_tag(tag_t tag, ...)
{
	va_list vl;
	va_start(vl, tag);
	
	mbp_buffer[mbp_index++] = tag;

	uint32_t length;
	switch(tag){

	case RELEASE_BUFFER:
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = 0;
		break;

	case GET_PITCH:
	case GET_ALPHA_MODE:
	case GET_PIXEL_ORDER:
	case GET_DEPTH:
	case GET_DMA_CHANNELS:
	case GET_BOARD_REVISION:
	case GET_BOARD_MODEL:
	case GET_FIRMWARE_REVISION:
		mbp_buffer[mbp_index++] = 4;
		mbp_buffer[mbp_index++] = 0;
		mbp_index += 1;
		break;

	case SET_ALPHA_MODE:
	case TEST_ALPHA_MODE:
	case SET_PIXEL_ORDER:
	case TEST_PIXEL_ORDER:
	case SET_DEPTH:
	case TEST_DEPTH:
	case BLANK_SCREEN:
	case RELEASE_MEMORY:
	case UNLOCK_MEMORY:
	case LOCK_MEMORY:
		mbp_buffer[mbp_index++] = 4;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 1;
		break;

	case ALLOCATE_MEMORY:
		mbp_buffer[mbp_index++] = 4;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 1;
		break;

	case SET_CURSOR_STATE:
		mbp_buffer[mbp_index++] = 4;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 1;
		break;
		
	case SET_CURSOR_INFO:
		mbp_buffer[mbp_index++] = 4;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_index += 1;
		break;

	case SET_PALETTE:
	case TEST_PALETTE:
		length = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = 4;
		mbp_buffer[mbp_index++] = 0;
		for(int i = 0; i < length >> 2; ++i){
			mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		}
		mbp_index += 1;
		break;


	case GET_VIRTUAL_OFFSET:
	case GET_VIRTUAL_BUFFER:
	case GET_PHYSICAL_DISPLAY:
	case GET_VC_MEMORY:
	case GET_ARM_MEMORY:
	case GET_BOARD_SERIAL:
	case GET_BOARD_MAC_ADDR:
		mbp_buffer[mbp_index++] = 8;
		mbp_buffer[mbp_index++] = 0;
		mbp_index += 2;
		break;

	case SET_VIRTUAL_OFFSET:
	case TEST_VIRTUAL_OFFSET:
	case ALLOCATE_BUFFER:
	case GET_DISPMANX_MEM_HANDLE:
	case GET_TEMPERATURE:
	case GET_MIN_VOLTAGE:
	case GET_MAX_VOLTAGE:
	case GET_VOLTAGE:
	case GET_TURBO:
	case GET_MIN_CLOCK_RATE:
	case GET_MAX_CLOCK_RATE:
	case GET_CLOCK_RATE:
	case GET_CLOCK_STATE:
	case GET_TIMING:
	case GET_POWER_STATE:
		mbp_buffer[mbp_index++] = 8;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 2;
		break;

	case SET_VIRTUAL_BUFFER:
	case TEST_VIRTUAL_BUFFER:
	case SET_PHYSICAL_DISPLAY:
	case TEST_PHYSICAL_DISPLAY:
	case SET_VOLTAGE:
	case SET_TURBO:
	case SET_CLOCK_STATE:
	case SET_POWER_STATE:
		mbp_buffer[mbp_index++] = 8;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 2;
		break;

	case SET_CLOCK_RATE:
		mbp_buffer[mbp_index++] = 8;
		mbp_buffer[mbp_index++]= 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 2;
		break;


	case GET_OVERSCAN:
		mbp_buffer[mbp_index++] = 16;
		mbp_buffer[mbp_index++] = 0;
		mbp_index += 16 >> 2;
		break;

	case SET_OVERSCAN:
	case TEST_OVERSCAN:
		mbp_buffer[mbp_index++] = 16;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 16 >> 2;
		break;
		
	case EXECUTE_CODE:
		mbp_buffer[mbp_index++] = 28;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++]= va_arg(vl, uint32_t);
		mbp_index += 28 >> 2;
		break;

	case GET_EDID_BLOCK:
		mbp_buffer[mbp_index++] = 136;
		mbp_buffer[mbp_index++] = 0;
		mbp_buffer[mbp_index++] = va_arg(vl, uint32_t);
		mbp_index += 136 >> 2;
		break;
		

	case GET_PALETTE:
		mbp_buffer[mbp_index++] = 1024;
		mbp_buffer[mbp_index++] = 0;
		mbp_index += 1024 >> 2;
		break;

		
	case GET_COMMAND_LINE:
	case GET_CLOCKS:
		length = va_arg(vl, uint32_t);
		mbp_buffer[mbp_index++] = length;
		mbp_buffer[mbp_index++] = 0;
		mbp_index += length >> 2;
		break;
		
	}
	mbp_buffer[mbp_index] = 0;
	va_end(vl);
}


uint32_t read_mailbox(mailbox_channel_t channel)
{
    for(;;){
		while(mailbox->status & MAILBOX_EMPTY){}
		uint32_t value = mailbox->read;
		if((value & 0xf) == channel){
			return (value >> 4);
		}
	}
}

void write_mailbox(mailbox_channel_t channel, uint32_t data)
{
	while(mailbox->status & MAILBOX_FULL){}
	data = (data << 4) | channel;
	mailbox->write = data;
}

uint32_t mailbox_property_finish(void)
{
	mbp_buffer[MBP_SIZE] = (mbp_index + 1) << 2;
	mbp_buffer[MBP_REQUEST_RESPONSE] = 0;
	write_mailbox(P_TAGS_ARM2VC, mbp_buffer);
	return read_mailbox(P_TAGS_ARM2VC);
}

uint8_t* mailbox_get_data(tag_t tag)
{
	uint32_t size = mbp_buffer[MBP_SIZE];
	uint32_t mem = mbp_buffer[MBP_DATA];

	while(mem < size){
		
	}
}
