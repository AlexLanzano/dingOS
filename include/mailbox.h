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
	GET_FIRMWARE_REVISION = 0x1,

	SET_CURSOR_INFO = 0x8010, 
	SET_CURSOR_STATE,
	
	GET_BOARD_MODEL = 0x10001,
	GET_BOARD_REVISION,
	GET_BOARD_MAC_ADDR, 
	GET_BOARD_SERIAL,   
	GET_ARM_MEMORY,     
	GET_VC_MEMORY,      
	GET_CLOCKS,


	GET_POWER_STATE = 0x20001,
	GET_TIMING,
	
	SET_POWER_STATE = 0x28001,

	GET_CLOCK_STATE = 0x30001,
	GET_CLOCK_RATE,     
	GET_VOLTAGE,        
	GET_MAX_CLOCK_RATE, 
	GET_MAX_VOLTAGE,    
	GET_TEMPERATURE,    
	GET_MIN_CLOCK_RATE, 
	GET_MIN_VOLTAGE,    
	GET_TURBO,          
	GET_MAX_TEMPERATURE,
	
	ALLOCATE_MEMORY = 0x3000c,
	LOCK_MEMORY,
	UNLOCK_MEMORY,
	RELEASE_MEMORY,
	EXECUTE_CODE,
	
	GET_DISPMANX_MEM_HANDLE = 0x30014,
	
	GET_EDID_BLOCK = 0x30020,

	SET_CLOCK_STATE = 0x38001,
	SET_CLOCK_RATE,
	SET_VOLTAGE,
	
	SET_TURBO = 0x38009,

	ALLOCATE_BUFFER = 0x40001,
	BLANK_SCREEN,
	GET_PHYSICAL_DISPLAY,
	GET_VIRTUAL_BUFFER,
	GET_DEPTH,
	GET_PIXEL_ORDER,
	GET_ALPHA_MODE,
	GET_PITCH,
	GET_VIRTUAL_OFFSET,
	GET_OVERSCAN,
	GET_PALETTE,

	TEST_PHYSICAL_DISPLAY = 0x44003,
	TEST_VIRTUAL_BUFFER,
	TEST_DEPTH,
	TEST_PIXEL_ORDER,
	TEST_ALPHA_MODE,
	
	TEST_VIRTUAL_OFFSET = 0x44009,
	TEST_OVERSCAN,
	
	SET_PHYSICAL_DISPLAY = 0x48003,
	SET_VIRTUAL_BUFFER,
	SET_DEPTH,
	SET_PIXEL_ORDER,
	SET_ALPHA_MODE,
	
	SET_VIRTUAL_OFFSET = 0x48009,
	SET_OVERSCAN,

	GET_COMMAND_LINE = 0x50001,

	GET_DMA_CHANNELS = 0x60001

	
} tag_t;


typedef enum{
	SD_CARD = 0x0,
	UART0,
	UART1,
	USB_HCD,
	I2C0,
	I2C1,
	I2C2,
	SPI,
	CCP2TX
} device_id_t;

typedef enum{
	reserved = 0x0,
	EMMC,
	UART,
	ARM,
	CORE,
	V3D,
	H264,
	ISP,
	SDRAM,
	PIXEL,
	PWM
} clock_id_t;

typedef enum{
	reserved = 0x0,
	CORE,
	SDRAM_C,
	SDRAM_P,
	SDRAM_I
} voltage_id_t;

typedef struct{
	volatile uint32_t read;
	volatile uint32_t write;
	volatile uint32_t peek;
	volatile uint32_t status;
	volatile uint32_t sender;
	volatile uint32_t config;
} mailbox_t;

typedef struct{
	uint32_t physical_width;
	uint32_t physical_height;
	uint32_t virtual_width;
	uint32_t virtual_height;
	uint32_t pitch;
	uint32_t depth;
	uint32_t x_offset;
	uint32_t y_offset;
	uint32_t address;
	uint32_t size;
} mailbox_framebuffer_t;

void mailbox_property_init(void);
void mailbox_property_add_tag(tag_t tag, ...);
uint32_t read_mailbox(mailbox_channel_t channel);
void write_mailbox(mailbox_channel_t channel, uint32_t data);

#endif
