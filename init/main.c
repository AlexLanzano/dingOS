#include <stdint.h>
#include <stddef.h>
#include <gpio.h>
#include <timer.h>
#include <interrupt.h>
#include <arm_timer.h>
#include <alloc.h>
#include <draw.h>
#include <mini_uart.h>


#define WIDTH 1920
#define HEIGHT 1080
#define DEPTH 32

#define ARM_TIMER_CTL 0x3f00B408
#define ARM_TIMER_CNT 0x3f00B420


#define KEY_ENTER     13
#define KEY_BACKSPACE 127

#define KEY_ESC       27
#define KEY_SYM_2     91

#define KEY_UP        65
#define KEY_DOWN      66
#define KEY_LEFT      68
#define KEY_RIGHT     67

extern int _kernel_start;
extern int _kernel_end;

int _enable_interrupts(void);
uint32_t* frame_buffer_init(uint32_t width, uint32_t height, uint32_t depth);
void mailbox_write(uint8_t channel, uint32_t value);
uint32_t mailbox_read(uint8_t channel);
uint32_t get_frame_buffer(void);
uint32_t get_pitch(void);
void draw_char(char c, uint32_t x, uint32_t y, uint32_t color);
uint8_t check_mem_loc(void);
void DrawPixel(uint32_t x, uint32_t y, uint32_t buffer);

void write32(uint32_t addr, uint32_t value);

void itoa(uint32_t i, char *str)
{
	
	char inverse_str[10];
	uint32_t inv_str_i = 0;
	while(i != 0){
		char c = (char)((i % 10) + 48);
		inverse_str[inv_str_i++] = c;
		i /= 10;
	}
	inverse_str[inv_str_i] = 0;
	int str_i = 0;
	int i_str_i = inv_str_i - 1;
	while(i_str_i > -1){
		str[str_i++] = inverse_str[i_str_i--];
	}
	str[str_i] = 0;
}


void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{

	uart_init();
	//write32(ARM_TIMER_CTL,0x00F90000);
	//write32(ARM_TIMER_CTL,0x00F90200);
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


	int x = 0;
	int y = 0;
	while(1){
		uint32_t c = uart_getc();

		if(c == KEY_ESC){
			c = uart_getc();
			if(c == 91){
				c = uart_getc();
				if(c == KEY_UP){
					
				}
				if(c == KEY_DOWN){
					
				}
				if(c == KEY_LEFT){
					
				}
				if(c == KEY_RIGHT){
					
				}
				
			}
		}

		if(c == KEY_ENTER){
			y += 16;
			x = 0;
		}
		if(c == KEY_BACKSPACE){
			
		}

		draw_char(c, x, y, 0x00000000);
		x += 8;
		if(x >= WIDTH){
			x = 0;
			y += 16;
		}

		
	}

	
}
