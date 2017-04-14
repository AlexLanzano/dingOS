#include <stdint.h>
#include <stddef.h>

#include <gpio.h>
#include <timer.h>
#include <interrupt.h>
#include <arm_timer.h>
#include <alloc.h>
#include <draw.h>
#include <aux.h>

#define WIDTH 1360
#define HEIGHT 768
#define DEPTH 32

#define ARM_TIMER_CTL 0x3f00B408
#define ARM_TIMER_CNT 0x3f00B420

extern int _kernel_start;
extern int _kernel_end;

int _enable_interrupts(void);
uint32_t* frame_buffer_init(uint32_t width, uint32_t height, uint32_t depth);
void mailbox_write(uint8_t channel, uint32_t value);
uint32_t mailbox_read(uint8_t channel);
uint32_t get_frame_buffer(void);
uint32_t get_pitch(void);
void draw_char(char c, uint32_t x, uint32_t y);
uint8_t check_mem_loc(void);
void DrawPixel(uint32_t x, uint32_t y, uint32_t buffer);

void write32(uint32_t addr, uint32_t value);

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{

	write32(ARM_TIMER_CTL,0x00F90000);
	write32(ARM_TIMER_CTL,0x00F90200);
	gpio_select_function(47, 1); // turn ack LED into output
	
	//	get_interrupt_controller()->enable_basic_irq = ARM_TIMER;
	//get_arm_timer()->load = 0x400;

	uint32_t color = 0xffffffff;
	/*
	get_arm_timer()->control =
		ARM_TIMER_CTRL_23BIT |
		ARM_TIMER_CTRL_ENABLE |
		ARM_TIMER_CTRL_INT_ENABLE |
		ARM_TIMER_CTRL_PRESCALE_256;
	*/
	//_enable_interrupts();
	//aux_mini_uart_init(115200, 8);
	//aux_mini_uart_putc('a');
	
	uint32_t *frame_buffer = (uint32_t *)frame_buffer_init(WIDTH, HEIGHT, DEPTH);
	//ACK_ON();

	uint32_t *buffer = (uint32_t *)get_frame_buffer();
	uint32_t pitch = get_pitch();
	
	init_screen_buffer(buffer, WIDTH, HEIGHT, DEPTH, pitch);
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			//write32(buffer, color);
			draw_pixel(x, y, color);
			//buffer += 4;
		}
	}

	draw_rect(10, 10, 100, 100, 0x00000000);
	draw_string("hello", 50, 50, 0x00000000);
	/*
	color = 0x00;
	char *string = "Hello";
	uint32_t fgh = 10;
	while(*string != 0){
		draw_char(*string, fgh, 10);
		string++;
		fgh += 8;
	}
	//draw_char('e', 18, 10);
	ACK_ON();

	draw_string("hello", 50, 50, color);
	*/	
/*
	int y = 0;
	for(int x = 0; x < WIDTH; ++x)
		buffer[x] = 0xffffff00;

	y = 2;
	for(int x = 0; x < WIDTH; ++x)
		buffer[(y * pitch) + x] = 0xffff0000;
	*/
	while(1){
		
	}

	
}
